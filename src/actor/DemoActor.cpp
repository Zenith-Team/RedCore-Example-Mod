#include <actor/Actor.h>
#include <graphics/AnimModel.h>
#include <example/ExampleMod.h>
#include <telkin/Print.h>

namespace example {

class DemoActor : public Actor {
    SEAD_RTTI_OVERRIDE(DemoActor, Actor)

public:
    static Profile* sProfile;

public:
    DemoActor(const ActorCreateParam& param);
    ~DemoActor() override = default;
    
    Result create() override;
    bool execute() override;
    bool draw() override;

private:
    AnimModel* mModel;
};

SEAD_RTTI_OVERRIDE_IMPL(DemoActor, Actor)

Profile* DemoActor::sProfile = example::getRegistrar()->newProfile<DemoActor>("demo")
    .resources<"star_coin">(ProfileInfo::cResType_Course)
    .build();

DemoActor::DemoActor(const ActorCreateParam& param)
    : Actor(param)
    , mModel(nullptr)
{ }

ActorBase::Result DemoActor::create() {
    tk::println("DemoActor was created!");

    mModel = AnimModel::create("star_coin", "star_coinA");

    return cResult_Success;
}

bool DemoActor::execute() {
    mAngle.y() += sead::Mathf::deg2idx(1.0f); // spin 1 degree per frame

    mModel->update(mPos, mAngle, mScale);

    return true;
}

bool DemoActor::draw() {
    mModel->draw();

    return true;
}

} // namespace example
