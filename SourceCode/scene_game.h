#pragma once

//******************************************************************************
//
//
//      �Q�[���V�[��
//
//
//******************************************************************************

// Game�N���X
class Game : public Scene
{
public:
    // �����o�ϐ�
    VECTOR2 hpPos01;    // HP�o�[�̈ʒu
    VECTOR2 hpSize01;   // HP�o�[�̑傫��
    VECTOR4 hpColor01;  // HP�o�[�̐F
    VECTOR2 hpPos02;    // HP�o�[�̈ʒu
    VECTOR2 hpSize02;   // HP�o�[�̑傫��
    VECTOR4 hpColor02;  // HP�o�[�̐F

    VECTOR2 squarePos_ = { 0,0 };
    VECTOR2 squareScale_ = { 0.0f, 0.0f };
    float squareAngle_ = 0.0f;

private:
    // �����o�ϐ�
    OBJ2DManager*   obj2dManager_;
    BG*             bg_;
    bool            isPaused_;
    OBJ2D*          player_;
    static Game     instance_;
    bool playerModeFlag_;   // �v���C���[���[�h�̐؂�ւ��t���O
    int stageNo_;           // �X�e�[�W�ԍ�
    bool enemyXFlip_;       // �G�̌�����ۑ�
    int combo_;             // �R���{��
    int combo2_;            // �R���{���i�A�Łj
    int combo2Timer_;       // �R���{�̏o������
    int maxCombo_;          // �ő�R���{��
    int score_;             // �X�R�A��
    int appearScore_;       // �X�R�A�̏o��
    int scoreTimer_;        // �X�R�A�̏o������
    int maxScore_;          // �ő�X�R�A
    int pause_num_;         // �|�[�Y���̑I��p
    float pause_alpha_;     // �|�[�Y���ɕ\������e�L�X�g�̃��l
    int pause_alpha_num_;   // ���l���O�`�P�܂ŉ��������邽�߂̒l
    int perfectNum_;        // �p�[�t�F�N�g��
    int greatNum_;          // �O���C�g��
    int goodNum_;           // �O�b�h��
    int missNum_;           // �~�X��
    bool playerAlive_;      // �����m�F
    VECTOR2 G_L_Fusuma_Pos_ = { 0,0 };  // �����ʒu
    VECTOR2 G_R_Fusuma_Pos_ = { 0,0 };  // �E���ʒu
    int Fusuma_timer_ = 0;            // ���^�C�}�[
    float G_Fusuma_timer_ = 0;          // �������n�߂�܂ł̎���
    bool title_push_flg = false;        // �^�C�g���ւ�I�񂾎��̃t���O
    bool restart_push_flg = false;      // �Ē����I�񂾎��̃t���O
    VECTOR2 shuriken_Pos_[11] = {};     //�藠���ʒu�̏�����
    float shuriken_Angle_ = 0;          //�藠���̊p�x�̏�����


    static const int maxAppearTime_ = 120; // �ő�\������

    // �m�[�c����̕\������
    int notesTimer_;
    std::ostringstream notesText;

    VECTOR2 comboSize;   // �R���{�̑傫��
    VECTOR2 combo2Pos;   // �R���{2�̈ʒu
    VECTOR2 combo2Size;  // �R���{2�̑傫��
    VECTOR4 combo2Color; // �R���{2�̐F

    VECTOR2 scorePos;    // �X�R�A�̈ʒu
    VECTOR2 scoreSize;   // �X�R�A�̑傫��
    VECTOR4 scoreColor;  // �X�R�A�̐F

    VECTOR2 notesPos;    // �m�[�c����̈ʒu
    VECTOR2 notesSize;   // �m�[�c����̑傫��
    VECTOR4 notesColor;  // �m�[�c����̐F

    VECTOR2 t_EndPos;    // �����̈ʒu
    VECTOR2 t_EndScale;  // �����̑傫��
    VECTOR2 t_EndSize;   // �����̑傫��
    VECTOR4 t_EndColor;  // �����̐F

    VECTOR2 t_FullComboPos;    // �����̈ʒu
    VECTOR2 t_FullComboScale;  // �����̑傫��
    VECTOR2 t_FullComboSize;   // �����̑傫��
    VECTOR4 t_FullComboColor;  // �����̐F
public:
    enum DECISION {
        MISS,
        GOOD,
        GREAT,
        PERFECT,
        NONE
    }decision_;

    void init() override;
    void deinit() override;
    void update() override;
    void draw() override;
    
    // �Q�b�^�[
    static Game* instance() { return &instance_; }

    OBJ2DManager* obj2dManager() { return obj2dManager_; }
    BG* bg() { return bg_; }
    bool playerModeFlag() { return playerModeFlag_; }
    int stageNo() { return stageNo_; }
    bool enemyXFlip() { return enemyXFlip_; }
    int timer() { return timer_; }
    int combo() { return combo_; }
    int combo2() { return combo2_; }
    int maxCombo() { return maxCombo_; }
    int score() { return score_; }
    int appearScore() { return appearScore_; }
    int maxScore() { return maxScore_; }
    int decision() { return decision_; }
    int maxAppearTime() { return maxAppearTime_; }
    int perfectNum() { return perfectNum_; }
    int greatNum() { return greatNum_; }
    int goodNum() { return goodNum_; }
    int missNum() { return missNum_; }
    bool playerAlive() { return playerAlive_; }

    // �Z�b�^�[
    OBJ2D* player() const { return player_; }
    void setPlayerModeFlag(bool f) { playerModeFlag_ = f; }
    void setStageNo(int n) { stageNo_ = n; }
    void setEnemyXFlip(bool f) { enemyXFlip_ = f; }
    void setCombo(int c) { combo_ = c; }
    void setCombo2(int c) { combo2_ = c; }
    void addCombo() { combo_++; }
    void addCombo2() { combo2_++; }
    void setComboSize(VECTOR2 s) { comboSize = s; }
    void setCombo2Timer(int t) { combo2Timer_ = t; }
    void setMaxCombo(int c) { maxCombo_ = c; }
    void setScore(int s) { score_ = s; }
    void setScoreTimer(int t) { scoreTimer_ = t; }
    void setAppearScore(int s) { appearScore_ = s; }
    void addScore(int s) { score_ += s; }
    void setMaxScore(int s) { maxScore_ = s; }
    void setDecision(DECISION d) {decision_ = d; }
    void deleteCombo() { combo_ = 0; }
    void deleteCombo2() { combo2_ = 0; }
    void addPerfectNum() { perfectNum_++; }
    void addGreatNum() { greatNum_++; }
    void addGoodNum() { goodNum_++; }
    void addMissNum() { missNum_++; }
    void setPlayerAlive(bool a) { playerAlive_ = a; }

private:
    // �R���X�g���N�^
    Game()
        :obj2dManager_(nullptr)
        , bg_(nullptr)
        , isPaused_(false)
        , player_(nullptr)
        , playerModeFlag_(false)
        , stageNo_(0)
        , enemyXFlip_(false)
        , combo_(0)
        , combo2_(0)
        , combo2Timer_(0)
        , maxCombo_(0)
        , score_(0)
        , scoreTimer_(0)
        , appearScore_(500)
        , maxScore_(0)
        , decision_(NONE)
        , notesTimer_(0)
        , hpPos01(0, 0)
        , hpSize01(0, 0)
        , hpColor01(0, 0, 0, 0)
        , hpPos02(0, 0)
        , hpSize02(0, 0)
        , hpColor02(0, 0, 0, 0)
        , pause_num_(0)
        , pause_alpha_(1.0f)
        , pause_alpha_num_(0)
        , perfectNum_(0)
        , greatNum_(0)
        , goodNum_(0)
        , missNum_(0)
        , playerAlive_(true)
        , squarePos_({0,0})
        , squareScale_({0.0f,0.0f})
        , squareAngle_(0.0f)
        , G_L_Fusuma_Pos_({ 0.0f,0.0f })  
        , G_R_Fusuma_Pos_({ 0.0f,0.0f })
        , G_Fusuma_timer_(0)
        , title_push_flg(false)
        , restart_push_flg(false)
        , Fusuma_timer_(0)

    {}
    Game(const Game&) = delete; // = delete �R�s�[�R���X�g���N�^�����݂��Ȃ����Ƃ𖾎�
    // �����蔻��
    void judge();
    
    // �R���{�̌v�Z
    void calcCombo();
    
    // �R���{�̕`��
    void comboDraw();

    // �X�R�A�̌v�Z
    void calcScore();

    // �X�R�A�̕`��
    void scoreDraw();

    // �m�[�c����
    void decisionJudge();

    // �m�[�c����̕`��
    void decisionDraw();

    // ������@UI
    void operationDraw();


public:
    //�g�p����X�v���C�g�f�[�^
    GameLib::SpriteData sprRestart_ = SPRITE_CENTER(static_cast<INT>(TEXNO::RESTART), 0, 0, 600, 300);
    GameLib::SpriteData sprTotitle_ = SPRITE_CENTER(static_cast<INT>(TEXNO::TOTITLE), 0, 0, 600, 300);
    GameLib::SpriteData sprL_Fusuma_ = SPRITE_CENTER(static_cast<INT>(TEXNO::L_FUSUMA), 0, 0, 960, 1080);
    GameLib::SpriteData sprR_Fusuma_ = SPRITE_CENTER(static_cast<INT>(TEXNO::R_FUSUMA), 0, 0, 960, 1080);
    GameLib::SpriteData sprShuriken_ = SPRITE_CENTER(static_cast<INT>(TEXNO::ENEMY0), 0, 0, 128, 128);
};

//******************************************************************************

