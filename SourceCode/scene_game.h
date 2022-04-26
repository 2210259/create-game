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
    int maxCombo_;          // �ő�R���{
    int score_;             // �X�R�A��
    int maxScore_;          // �ő�X�R�A

    // �m�[�c����̕\������(��)
    int goodTimer;
    int greatTimer;
    int perfectTimer;

public:
    enum DECISION {
        MISS,
        GOOD,
        GREAT,
        PERFECT,
        MAX
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
    int maxCombo() { return maxCombo_; }
    int score() { return score_; }
    int maxScore() { return maxScore_; }
    int decision() { return decision_; }

    // �Z�b�^�[
    OBJ2D* player() const { return player_; }
    void setPlayerModeFlag(bool f) { playerModeFlag_ = f; }
    void setStageNo(int n) { stageNo_ = n; }
    void setEnemyXFlip(bool f) { enemyXFlip_ = f; }
    void setCombo(int c) { combo_ = c; }
    void addCombo() { combo_++; }
    void setMaxCombo(int c) { maxCombo_ = c; }
    void setScore(int s) { score_ = s; }
    void addScore(int s) { score_ += s; }
    void setMaxScore(int c) { maxScore_ = c; }
    void setDecision(DECISION d) {decision_ = d; }
    void deleteCombo() { combo_ = 0; }

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
        , maxCombo_(0)
        , score_(0)
        , maxScore_(0)
        , decision_(MISS)
        , goodTimer(0)
        , greatTimer(0)
        , perfectTimer(0)
        , hpPos01(0, 0)
        , hpSize01(0, 0)
        , hpColor01(0, 0, 0, 0)
        , hpPos02(0, 0)
        , hpSize02(0, 0)
        , hpColor02(0, 0, 0, 0)
    {}
    Game(const Game&) = delete; // = delete �R�s�[�R���X�g���N�^�����݂��Ȃ����Ƃ𖾎�
    // �����蔻��
    void judge();
    
    // �ő�R���{�̌v�Z
    void calcMaxCombo();
    
    // �R���{�̕`��
    void comboDraw();

    // �X�R�A�̕`��
    void scoreDraw();

    // �m�[�c����
    void decisionJudge();

    // �m�[�c����̕`��
    void decisionDraw();
};

//******************************************************************************

