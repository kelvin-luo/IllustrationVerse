/*
    Copyright (C) 2021  kelvin-luo

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

    My Github homepage: https://github.com/kelvin-luo
*/
//#pragma encoding("UTF-8")
//#pragma execution_character_set("utf-8")

#include "utility.h"

#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>

#if defined(Q_OS_WIN)
#include <windows.h>
#include <shellapi.h>
#endif

const QString models_dir = ".";

Utility::Utility() {}

bool createDirectoryIfNotExists(const QString &path)
{
  const QString clean = QDir::cleanPath(path);
  QDir dir(clean);

  // 检查目录是否存在
  if (dir.exists())
  {
    qDebug() << "目录已存在";
    return true; // 目录已存在，返回成功
  }

  // 尝试创建目录（包括所有必要的父目录）
  qDebug() << "尝试创建目录" << clean;
  return QDir().mkpath(clean);
}

// 将 QDate 转换为字符串，格式："yyyy-MM-dd"
QString dateToString(const QDate &date) { return date.toString("yyyy-MM-dd"); }

// 将 QTime 转换为字符串，格式："HH:mm:ss"
QString timeToString(const QTime &time) { return time.toString("HH:mm:ss"); }

// 将 QDateTime 转换为字符串，格式："yyyy-MM-dd HH:mm:ss"
QString dateTimeToString(const QDateTime &dateTime)
{
  // return dateTime.toString("yyyy_MM_dd_HH_mm_ss");
  return dateTime.toString("yyMMdd_HHmmss");
}

bool writeStringToJsonFile(const QString &filePath, const QString &key,
                           const QString &value)
{
  QFile file(filePath);

  // 打开文件进行读写
  if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
  {
    qDebug() << "无法打开文件:" << filePath;
    return false;
  }

  QJsonDocument doc;
  QJsonObject jsonObject;

  // 如果文件不为空，读取现有 JSON 内容
  if (file.size() > 0)
  {
    QByteArray data = file.readAll();
    QJsonParseError parseError;
    doc = QJsonDocument::fromJson(data, &parseError);

    if (parseError.error != QJsonParseError::NoError)
    {
      qDebug() << "JSON 解析错误:" << parseError.errorString();
      file.close();
      return false;
    }

    if (doc.isObject())
    {
      jsonObject = doc.object();
    }
  }

  // 设置新的键值对
  jsonObject[key] = QJsonValue(value);

  // 重置文件指针并写入更新后的 JSON
  file.resize(0);
  QTextStream stream(&file);
  // stream.setCodec("UTF-8");//!< 在qt6中已经不用这样了.
  stream << QJsonDocument(jsonObject).toJson(QJsonDocument::Indented);

  file.close();
  return true;
}

 
QString genCmd(tp_stru_command_string cmd, SD_Model_type modelCls)
{
  QString cmd_str = cmd.exeFile;

  if (modelCls == SD_1_5 || modelCls == SDXL_1_0)
  {
    if (!cmd.checkpoint.isEmpty())
      cmd_str += " -m " + cmd.checkpoint;
    // qDebug() << "这是sd1.5模型或者sdxl模型。";
  }
  else if (modelCls == FLUX_1_0)
  {
    if (!cmd.checkpoint.isEmpty())
      cmd_str += " --diffusion-model " + cmd.checkpoint;
    // qDebug() << "这是flux1.0模型。";
  }
  else
  {
    if (!cmd.checkpoint.isEmpty())
      cmd_str += " --diffusion-model " + cmd.checkpoint;
    // qDebug() << "这是其他模型。";
  }

  if (!cmd.vae.isEmpty())
    cmd_str += " --vae " + cmd.vae;
  if (!cmd.clip_l.isEmpty())
    cmd_str += " --clip_l " + cmd.clip_l;
  if (!cmd.t5xxl.isEmpty())
    cmd_str += " --t5xxl " + cmd.t5xxl;
  // if(!cmd.PromptImgFile.isEmpty())cmd_str += " -p \""+cmd.PromptText + "\" ";
  if (!cmd.PromptText.isEmpty())
    cmd_str += " -p \"" + cmd.PromptText + "\" ";
  if (!cmd.embd_dir.isEmpty())
    cmd_str += " --embd-dir  " + cmd.embd_dir;
  if (!cmd.lora_model_dir.isEmpty())
    cmd_str += " --lora-model-dir " + cmd.lora_model_dir;
  if (!cmd.negative_PromptText.isEmpty())
    cmd_str += " -n \"" + cmd.negative_PromptText + "\" ";

  cmd_str += " --cfg-scale  " + QString::number(cmd.cfg_scale);
  cmd_str += " --strength  " + QString::number(cmd.unoising_strength);
  cmd_str += "  --steps   " + QString::number(cmd.steps);

  if (!cmd.sampling_method.isEmpty())
    cmd_str += " --sampling-method  " + cmd.sampling_method;

  if (!cmd.schedule.isEmpty())
    cmd_str += " --scheduler  " + cmd.schedule;

  cmd_str += " -W  " + QString::number(cmd.latentImgWidth);
  cmd_str += " -H  " + QString::number(cmd.latentImgHeight);
  cmd_str += " --batch-count  " + QString::number(cmd.batch_count);

  cmd_str +=
      "  -v -o " + cmd.resultImgFile + " -s " + QString::number(cmd.seed);
  cmd_str += " -t 12 ";
  return cmd_str;

#if 0
    return QString(cmd.exeFile+ " --diffusion-model "+cmd.checkpoint+ " --vae "+cmd.vae+" --clip_l "+ cmd.clip_l+"  --t5xxl "+cmd.t5xxl+"   -p  "+cmd.PromptText +" --cfg-scale "+QString::number(cmd.cfg_scale)+" --sampling-method  "+cmd.sampling_method+"  -v -o " + cmd.resultImgFile+" -s " + QString::number(cmd.seed) );
#endif
}

#if defined(Q_OS_WIN)
bool windowsCommandLineToProcessArgs(const QString &cmdLine, QString &outProgram,
                                     QStringList &outArguments)
{
  outProgram.clear();
  outArguments.clear();
  const QString trimmed = cmdLine.trimmed();
  if (trimmed.isEmpty())
    return false;

  int nArgs = 0;
  LPWSTR *argv = CommandLineToArgvW(reinterpret_cast<LPCWSTR>(trimmed.utf16()), &nArgs);
  if (!argv || nArgs < 1)
  {
    if (argv)
      LocalFree(argv);
    return false;
  }

  QStringList all;
  all.reserve(nArgs);
  for (int i = 0; i < nArgs; ++i)
    all.append(QString::fromWCharArray(argv[i]));
  LocalFree(argv);

  outProgram = all.first();
  if (nArgs > 1)
    outArguments = all.mid(1);

  if (!QFileInfo(outProgram).isAbsolute())
  {
    const QString base = QCoreApplication::applicationDirPath();
    outProgram = QDir(base).filePath(outProgram);
  }
  return true;
}
#endif
