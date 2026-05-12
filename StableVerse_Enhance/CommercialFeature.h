class CommercialFeature : public IFeatureService {
public:
    void execute() override {
        // 商业版增强实现
        // 可以调用开源版基础功能
        OpenSourceFeature::execute();
        // 添加商业版特有功能
    }
};