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
private:
    // �����o�ϐ�
    OBJ2DManager*   obj2dManager_;
    BG*             bg_;
    bool            isPaused_;
    OBJ2D*          player_;
    static Game     instance_;
    bool playerModeFlag_;  // �v���C���[���[�h�̐؂�ւ��t���O
    int stageNo_;          // �X�e�[�W�ԍ�
    bool enemyXFilip_;     // �G�̌�����ۑ�

public:
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
    bool enemyXFlip() { return enemyXFilip_; }

    // �Z�b�^�[
    void setPlayerModeFlag(bool f) { playerModeFlag_ = f; }
    void setStageNo(int n) { stageNo_ = n; }
    void setEnemyXFilip(bool f) { enemyXFilip_ = f; }

private:
    // �R���X�g���N�^
    Game()
        :obj2dManager_(nullptr)
        , bg_(nullptr)
        , isPaused_(false)
        , player_(nullptr)
        , playerModeFlag_(false)
        , stageNo_(0)
        , enemyXFilip_(false)
    {}
    Game(const Game&) = delete; // = delete �R�s�[�R���X�g���N�^�����݂��Ȃ����Ƃ𖾎�
    // �����蔻��
    void judge();
};

//******************************************************************************

