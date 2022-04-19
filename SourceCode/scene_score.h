#pragma once
class Score : public Scene
{
private:
    static Score instance_;

public:
    // �C���X�^���X�̎擾
    static Score* instance() { return &instance_; }

    void init() override;
    void deinit() override;
    void update() override;
    void draw() override;

private:
    Score() {}
    ~Score() {}

    Score(const Score&) = delete;                 // �R�s�[�R���X�g���N�^�[
    Score& operator=(const Score&) = delete;      // �R�s�[������Z�q
    Score(Score&&) noexcept = delete;             // ���[�u�R���X�g���N�^�[
    Score& operator=(Score&&) noexcept = delete;  // ���[�u������Z�q

//public:
//    // �g�p����e�N�X�`���̃��x��
//    enum class TEXNO {
//        STAR,
//        NUM,
//    };

//    // �g�p����X�v���C�g�f�[�^
//    GameLib::SpriteData sprStar_ = SPRITE_CENTER(static_cast<INT>(TEXNO::STAR), 0, 0, 500, 500);

//private:
//    // �t�F�[�h�A�E�g�p�^�C�}�[
//    //float fadeOutTimer_ = 0.0f;

//    // �����o�ϐ�
//    VECTOR2 starScale_ = { 0.0f, 0.0f };
//    float   starAngle_ = 0.0f;
//    int stageNum_ = 0;
};