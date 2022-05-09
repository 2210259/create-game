#pragma once
class Score : public Scene
{
private:
    static Score instance_;

    int score_select_num_;   //�I��p
    float score_alpha_;      //�\������e�L�X�g�̃��l
    int score_alpha_num_;    //���l���O�`�P�܂ŉ��������邽�߂̒l

    VECTOR2 scoreText_pos_;  //�X�R�A�e�L�X�g�̈ʒu
    int     scoreNum_;       //�X�R�A

    VECTOR2 comboText_pos_;  //�R���{�e�L�X�g�̈ʒu
    int     comboNum_;       //�R���{

    VECTOR2 perfectText_pos_;//�p�[�t�F�N�g�e�L�X�g�̈ʒu
    int     perfectNum_;     //�p�[�t�F�N�g

    VECTOR2 greatText_pos_;  //�O���C�g�e�L�X�g�̈ʒu
    int     greatNum_;       //�O���C�g

    VECTOR2 goodText_pos_;   //�O�b�h�e�L�X�g�̈ʒu
    int     goodNum_;        //�O�b�h

    VECTOR2 missText_pos_;   //�~�X�e�L�X�g�̈ʒu
    int     missNum_;        //�~�X

    float rank_Scale;        //�����N�e�L�X�g�̃X�P�[��

    int     performState_;   //���o�p�X�e�[�g



public:
    // �C���X�^���X�̎擾
    static Score* instance() { return &instance_; }

    void init() override;
    void deinit() override;
    void update() override;
    void draw() override;

private:
    Score() 
        : score_select_num_(0)
        ,score_alpha_(1.0f)
        ,score_alpha_num_(0)
        , scoreText_pos_({ 1920.0f,0.0f })
        , scoreNum_(0)
        , perfectText_pos_({ 1920.0f,0.0f })
        , perfectNum_(0)
        , greatText_pos_({ 1920.0f,0.0f })
        , greatNum_(0)
        , goodText_pos_({ 1920.0f,0.0f })
        , goodNum_(0)
        , performState_(0)
        , missNum_(0)
        , missText_pos_({ 1920.0f,0.0f })
        , rank_Scale( 130.0f )
    {}
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

public:
    // �g�p����e�N�X�`���̃��x��
    enum class TEXNOM {
        RESTART,
        TOTITLE,
        CLEAR,
        GAMEOVER,
        NUM,
    };

    //�g�p����X�v���C�g�f�[�^
    GameLib::SpriteData sprRestart_ = SPRITE_CENTER(static_cast<INT>(TEXNOM::RESTART), 0, 0, 600, 300);
    GameLib::SpriteData sprTotitle_ = SPRITE_CENTER(static_cast<INT>(TEXNOM::TOTITLE), 0, 0, 600, 300);
    GameLib::SpriteData sprClear_ = SPRITE_CENTER(static_cast<INT>(TEXNOM::CLEAR), 0, 0, 1920, 1080);
    GameLib::SpriteData sprGameover_ = SPRITE_CENTER(static_cast<INT>(TEXNOM::GAMEOVER), 0, 0, 1920, 1080);

};