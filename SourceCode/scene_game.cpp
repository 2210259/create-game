//******************************************************************************
//
//
//      �Q�[�����
//
//
//******************************************************************************

//------< �C���N���[�h >---------------------------------------------------------
#include "all.h"
#include <sstream>
#include <iomanip>

//------< using >---------------------------------------------------------------
using namespace GameLib;

//------< �ϐ� >----------------------------------------------------------------
Game Game::instance_;

//--------------------------------------------------------------
//  ����������
//--------------------------------------------------------------
void Game::init()
{
    Scene::init();	    // ���N���X��init���Ă�

    obj2dManager_   = new OBJ2DManager;
    bg_             = new BG;

    isPaused_ = false;   // �|�[�Y�t���O�̏�����
}

//--------------------------------------------------------------
//  �I������
//--------------------------------------------------------------
void Game::deinit()
{
    // �e�}�l�[�W���̉��
    safe_delete(bg_);
    safe_delete(obj2dManager_);

    // �e�N�X�`���̉��
    texture::releaseAll();

    // TODO:���y����Ȃ�������R�����g�A�E�g
    // ���y�̃N���A 
    // music::clear();
}

//--------------------------------------------------------------
//  �X�V����
//--------------------------------------------------------------
void Game::update()
{
    using namespace input;

    // �X�e�[�W�Z���N�g
    if ((STATE(0) & PAD_SELECT) && (STATE(0) & PAD_START))
    {
        changeScene(Title::instance()); // �^�C�g���V�[���ɐ؂�ւ���
        return;
    }

     debug::setString("isPaused_%d", isPaused_);

    // �|�[�Y����
     if (TRG(0) & PAD_TRG1)
     {
         //���y���ĊJ
         GameLib::music::resume(0);

         // 0�R���̃X�^�[�g�{�^���������ꂽ��|�[�Y��Ԃ����]
         isPaused_ = !isPaused_;        
     }

     //�|�[�Y��
     if (isPaused_)
     {
         // A�L�[�������ꂽ��
         if (TRG(0) & PAD_RIGHT)
         {
             if (pause_num_ > 0)
             {
                 pause_num_--;
             }
         }

         //�@D�L�[�������ꂽ��
         if (TRG(0) & PAD_LEFT)
         {
             if (pause_num_ < 1)
             {
                 pause_num_++;
             }
         }

         //���y���~�߂�
         GameLib::music::pause(0);

         //�����̃��l���O�`�P�̊Ԃŉ��������鏈��
         switch (pause_alpha_num_)
         {
         case 0:
             pause_alpha_ -= 0.03f;
             if (pause_alpha_ <= 0)   pause_alpha_num_++;
             break;

         case 1:
             pause_alpha_ += 0.03f;
             if (pause_alpha_ >= 1)   pause_alpha_num_--;
             break;
         }

         //�O(�Ē���)��I��ł���Ƃ�
         if (pause_num_)
         {
             if (TRG(0) & PAD_START)
             {
                 music::play(7);
                 changeScene(Game::instance());
             }
         }

         //�P(�����Ƃ��)��I��ł���Ƃ�
         if (pause_num_ == false)
         {
             if (TRG(0) & PAD_START)
             {
                 music::play(7);
                 changeScene(Title::instance());
             }
         }

         return;              // ���̎��_�Ń|�[�Y���Ȃ烊�^�[��
     }

    switch (state_)
    {
    case 0:
        //////// �����ݒ� ////////
        
        timer_       = 0;    // �Q�[���^�C�}�[
        combo2Timer_ = 0;
        scoreTimer_  = 0;    // �X�R�A�^�C�}�[
        notesTimer_  = 0;    // �m�[�c�^�C�}�[
        score_       = 0;    // �X�R�A
        combo_       = 0;    // �R���{��
        combo2_      = 0;    // �R���{��(�A��)
        maxCombo_    = 0;    // �ő�R���{��

        // HP�o�[�̐ݒ�
        hpPos01      = { 950,  20 };         // HP�o�[�̈ʒu
        hpSize01     = { 300,  60 };         // HP�o�[�̑傫��
        hpColor01    = { 0, 0, 0, 1.0f };    // HP�o�[�̐F
        hpPos02      = { 955,  25 };         // HP�o�[�̈ʒu
        hpSize02     = { 290,  50 };         // HP�o�[�̑傫��
        hpColor02    = { 1, 0, 0, 0.8f };    // HP�o�[�̐F
        comboSize    = { 1, 1 };             // �R���{�̑傫��
        combo2Pos    = { 1250, 240 };        // �R���{2�̈ʒu
        combo2Size   = { 1, 1 };             // �R���{2�̑傫��             
        combo2Color  = { 1, 1, 1, 0 };       // �R���{2�̐F
        scorePos     = { 10, 80 };           // �X�R�A�̈ʒu
        scoreSize    = { 1, 1 };             // �X�R�A�̑傫��             
        scoreColor   = { 1, 1, 1, 0 };       // �X�R�A�̐F
        notesPos     = { 1250, 200 };        // �m�[�c�̈ʒu
        notesSize    = { 1, 1 };             // �m�[�c�̑傫��             
        notesColor   = { 1, 1, 1, 0 };       // �m�[�c�̐F

        // BGM�̍Đ�
        music::play(0, false);

        GameLib::setBlendMode(Blender::BS_ALPHA);   // �ʏ�̃A���t�@����

        // �e�N�X�`���̓ǂݍ���
        texture::load(loadTexture);

        // �v���C���[�}�l�[�W���̏����ݒ�
        obj2dManager()->init();

        // �G���Z�b�g
        setEnemy(obj2dManager(), bg());

        // �v���C���[��ǉ�
        player_ = obj2dManager()->add(
            new OBJ2D(
                new Renderer,
                new Collider,
                bg(),
                new ActorComponent,
                nullptr
            ),
            &idlePlayerBehavior, VECTOR2(640, 700), -1, {});

        // BG�̏����ݒ�
        bg()->init(player_);

        state_++;    // �����ݒ菈���̏I��
        /*fallthrough*/

    case 1:
        //////// �ʏ펞�̏��� ////////

        // �I�u�W�F�N�g�̍X�V
        obj2dManager()->update();

        bg()->update();   // BG�̍X�V

        // �G���Z�b�g
        setEnemy(obj2dManager(), bg());

        // �����蔻��
        judge();

        // �X�R�A�̌v�Z
        calcScore();

        // �R���{�̌v�Z
        calcCombo();

        // �m�[�c����̍X�V
        decisionJudge();

        // TODO:�Q�[���̏I�����Ԃ̒���
        if (timer_ > 100) {
            GameLib::music::stop(0);
            changeScene(Score::instance());
            break;
        }
        timer_++;
        break;
    }
    // debug::setString("Combo:%d", combo());
    // debug::setString("maxCombo:%d", maxCombo());
    // 
    // debug::setString("stageNo:%d", Game::instance()->stageNo());
    // debug::setString("GameTimer:%d", timer_);
}

//--------------------------------------------------------------
//  �`�揈��
//--------------------------------------------------------------
void Game::draw()
{
    // ��ʃN���A
    GameLib::clear(VECTOR4(0.5f, 0.5f, 0.5f, 1));

    bg()->drawBack();   // �I�u�W�F�N�g�̕`��

    // �I�u�W�F�N�g�̕`��
    obj2dManager()->draw(bg()->getScrollPos());

    // HP�o�[�̕`��
    primitive::rect(hpPos01, hpSize01, { 0, 0 }, 0, hpColor01);
    if (player()->actorComponent()->hp() >= 0) {
        primitive::rect(hpPos02,
            { hpSize02.x / player()->actorComponent()->maxHP() * player()->actorComponent()->hp(), hpSize02.y },
            { 0, 0 }, 0, hpColor02);
    }

    // �X�R�A,�R���{���̕`��
    // TODO:�X�R�A�̕\��
    scoreDraw();
    comboDraw();

    // �m�[�c����̕`��
    decisionDraw();

    // ��������̕`��
    operationDraw();

    // �|�[�Y���
    if (isPaused_)
    {
        GameLib::font::textOut(4, "PAUSE",
            { GameLib::window::getWidth() / 2, (GameLib::window::getHeight() / 4) },
            VECTOR2(5.0f, 5.0f),
            { 1.0f, 1.0f, 1.0f, 1.0f },
            GameLib::TEXT_ALIGN::UPPER_MIDDLE
        );

        //�Ē����I��ł���Ƃ�
        if (pause_num_)
        {
            //"�Ē���"�̕����̕`��
            sprRestart_.draw(
                { GameLib::window::getWidth() / 4, GameLib::window::getHeight() / 2 + GameLib::window::getHeight() / 4 },
                { 1.0f,1.0f },
                ToRadian(0),
                { 1,1,1,pause_alpha_ }
            );

            //"�����Ƃ��"�̕����̕`��
            sprTotitle_.draw(
                { GameLib::window::getWidth() / 2 + GameLib::window::getWidth() / 4, GameLib::window::getHeight() / 2 + GameLib::window::getHeight() / 4 },
                { 1.0f,1.0f },
                ToRadian(0),
                { 1,1,1,1 }
            );
        }

        //�����Ƃ�ւ�I��ł���Ƃ�
        if (pause_num_ == false)
        {
            //"�Ē���"�̕����̕`��
            sprRestart_.draw(
                { GameLib::window::getWidth() / 4, GameLib::window::getHeight() / 2 + GameLib::window::getHeight() / 4 },
                { 1.0f,1.0f },
                ToRadian(0),
                { 1,1,1,1 }
            );

            //"�����Ƃ��"�̕����̕`��
            sprTotitle_.draw(
                { GameLib::window::getWidth() / 2 + GameLib::window::getWidth() / 4, GameLib::window::getHeight() / 2 + GameLib::window::getHeight() / 4 },
                { 1.0f,1.0f },
                ToRadian(0),
                { 1,1,1,pause_alpha_ }
            );
        }

    }

    //���̍U���͈͕\��
    primitive::rect(445, 610, 30, 30, 0, 0, ToRadian(0), 1.0f, 1.0f, 1.0f, 0.2f);
    //�E�̍U���͈͕\��
    primitive::rect(805, 610, 30, 30, 0, 0, ToRadian(0), 1.0f, 1.0f, 1.0f, 0.2f);
    //��̍U���͈͕\��
    primitive::rect(625, 430, 30, 30, 0, 0, ToRadian(0), 1.0f, 1.0f, 1.0f, 0.2f);

    //�v���C���[�����������Ă�����
    if (player()->actorComponent()->direction() == player()->actorComponent()->LEFT)
    {
        //���̍U���͈͕\��
        primitive::rect(445, 610, 30, 30, 0, 0, ToRadian(0), 1.0f, 1.0f, 1.0f, 0.6f);
    }
    //�v���C���[�����������Ă�����
    if (player()->actorComponent()->direction() == player()->actorComponent()->RIGHT)
    {
        //�E�̍U���͈͕\��
        primitive::rect(805, 610, 30, 30, 0, 0, ToRadian(0), 1.0f, 1.0f, 1.0f, 0.6f);
    }
     //�v���C���[�����������Ă�����
    if (player()->actorComponent()->direction() == player()->actorComponent()->UP)
    {
        //��̍U���͈͕\��
        primitive::rect(625, 430, 30, 30, 0, 0, ToRadian(0), 1.0f, 1.0f, 1.0f, 0.6f);
    }
}

//--------------------------------------------------------------
//  �����蔻��
//--------------------------------------------------------------
void Game::judge()
{
    for (auto& src : *obj2dManager()->getList())
    {
        if (!src->behavior()) continue;
        if (!src->collider()->judgeFlag()) continue;

        for (auto& dst : *obj2dManager()->getList())
        {
            if (!src->behavior()) break;

            if (src == dst) continue;   // �������g�͂Ƃ΂�
            if (!dst->behavior()) continue;
            if (!dst->collider()->judgeFlag()) continue;

            // src�̍U���^�C�v��dst�̃^�C�v����v���Ȃ����̂��Ƃ΂�
            if (src->behavior()->attackType() != dst->behavior()->getType())
                continue;

            // �����蔻����s��
            if (src->collider()->hitCheck(dst))
            {
                // ���������ꍇ�̏���
                src->behavior()->hit(src, dst);
            }
            else if (src->collider()->hitCheck2(dst))
            {
                src->behavior()->hit2(src, dst);
            }
            else if (src->collider()->hitCheck3(dst))
            {
                src->behavior()->hit3(src, dst);
            }
            else if (src->collider()->hitCheck5(dst))
            {
                src->behavior()->hit5(src, dst);
            }
            else if (src->collider()->hitCheck6(dst))
            {
                src->behavior()->hit6(src, dst);
            }
            else if (src->collider()->hitCheck7(dst))
            {
                src->behavior()->hit7(src, dst);
            }
            // ����������
            if (src->collider()->hitCheck4(dst))
            {
                src->behavior()->hit4(src, dst);
            }
        }
    }
}

void Game::calcCombo()
{
    // �ő�R���{�̍X�V
    if (combo() > maxCombo()) {
        setMaxCombo(combo());
    }

    // �X�R�A�\�������Ƃɖ߂�
    if (combo2Timer_ >= maxAppearTime_) {
        combo2Pos   = { 1250, 240 };        // �R���{�̈ʒu
        combo2Size  = { 1, 1 };             // �R���{�̑傫��
        combo2Color = { 1, 1, 1, 0 };       // �R���{�̐F
    }
    // �^�C�}�[�����炷
    if (combo2Timer_ > 0) combo2Timer_--;

    // �p�����[�^��ύX
    
    // �R���{1�̐ݒ�
    if (comboSize.x > 1.0f) 
        comboSize -= { 0.05f, 0.05f };

    // �R���{2�̐ݒ�
    if (combo2Timer_ > 30) {
        combo2Color.w += 0.5f;
    }
    else {
        combo2Color.w -= 0.04f;
    }
    if (combo2Timer_ > 115)
        combo2Size += { 0.1f, 0.1f };
    else
        combo2Size -= { 0.1f, 0.1f };

    // ���̒l�𒴂��Ȃ��悤�ɐݒ�
    combo2Size.x = clamp(combo2Size.x, 1.0f, 1.5f);
    combo2Size.y = clamp(combo2Size.y, 1.0f, 1.5f);
    if (combo2Pos.y < 240)        combo2Pos.y = 240;
    combo2Size.x = clamp(combo2Size.x, 1.0f, 1.3f);
    combo2Size.y = clamp(combo2Size.y, 1.0f, 1.3f);
    combo2Color.w = clamp(combo2Color.w, 0.0f, 1.0f);
}

// �R���{�̕`��ݒ�
void Game::comboDraw()
{
    std::ostringstream ss1, ss2, ss3;

    ss1 << "COMBO" << std::setw(4) << " ";
    ss2 << std::setw(9) << combo_;
    ss3 << combo2_;
    // �R���{�����e�L�X�g�\��
    font::textOut(6,
        ss1.str(),
        { 1250, 120 },
        { 1.0f, 1.0f },
        { 1.0f, 1.0f, 1.0f, 1.0f },
        TEXT_ALIGN::MIDDLE_RIGHT
    );

    font::textOut(6,
        ss2.str(),
        { 1250, 120 },
        comboSize,
        { 1.0f, 1.0f, 1.0f, 1.0f },
        TEXT_ALIGN::MIDDLE_RIGHT
    );
    
    if (combo2_ > 0 && combo2Timer_ > 0) {
        font::textOut(6,
            ss3.str(),
            combo2Pos,
            combo2Size,
            combo2Color,
            TEXT_ALIGN::MIDDLE_RIGHT
        );
    }
}

void Game::calcScore()
{
    // �X�R�A�\�������Ƃɖ߂�
    if (scoreTimer_ >= maxAppearTime_) {
        scorePos    = { 10, 80 };           // �X�R�A�̈ʒu
        scoreColor  = { 1.0f, 1.0f, 0.5f, 0 };       // �X�R�A�̐F
    }
    // �^�C�}�[�����炷
    if (scoreTimer_ > 0) scoreTimer_--;

    // �p�����[�^��ύX
    if (scoreTimer_ > 100) {
        scorePos.y -= 1.0f;
        scoreColor.w += 0.2f;
    }
    else{
        scorePos.y -= 1.0f;
        scoreColor.w -= 0.02f;
    }
    // ���̒l�𒴂��Ȃ��悤�ɐݒ�
    if (scorePos.y < 10)        scorePos.y = 10;
    scoreColor.w = clamp(scoreColor.w, 0.0f, 1.0f);
}

// �X�R�A�̕`��ݒ�
void Game::scoreDraw()
{
    std::ostringstream ss1, ss2;
    
    ss1 << "SCORE " << std::setw(8) << std::setfill('0') << score_;
    ss2 << std::setw(14) << appearScore_;
    
    // �X�R�A�����e�L�X�g�\��
    font::textOut(6,
        ss1.str(),
        { 10, 10 },
        { 1.0f, 1.0f },
        { 1.0f, 1.0f, 1.0f, 1.0f },
        TEXT_ALIGN::UPPER_LEFT
    );

    if (scoreTimer_) {
        // �X�R�A�����e�L�X�g�\��
        font::textOut(6,
            ss2.str(),
            scorePos,
            scoreSize,
            scoreColor,
            TEXT_ALIGN::UPPER_LEFT
        );
    }
}

// �m�[�c����̔���
void Game::decisionJudge()
{
    switch (decision_)
    {
    case Game::MISS:
        notesText.str("MISS");
        notesTimer_ = maxAppearTime_;
        notesPos    = { 1250, 200 };
        notesSize   = { 0.2f, 0.2f };
        notesColor  = { 0.0f, 0.0f, 1.0f, 0.0f };
        decision_   = NONE;
        break;
    case Game::GOOD:
        notesText.str("GOOD");
        notesTimer_ = maxAppearTime_;
        notesPos    = { 1250, 200 };
        notesSize   = { 0.2f, 0.2f };
        notesColor  = { 1.0f, 1.0f, 1.0f, 0.0f };
        decision_   = NONE;
        break;
    case Game::GREAT:
        notesText.str("GREAT");
        notesTimer_ = maxAppearTime_;
        notesPos    = { 1250, 200 };
        notesSize   = { 0.2f, 0.2f };
        notesColor  = { 0.2f, 1.0f, 1.0f, 0.0f };
        decision_   = NONE;
        break;
    case Game::PERFECT:
        notesText.str("PERFECT");
        notesTimer_ = maxAppearTime_;
        notesPos    = { 1250, 200 };
        notesSize   = { 0.2f, 0.2f };
        notesColor  = { 1.0f, 1.0f, 0.0f, 0.0f };
        decision_   = NONE;
        break;
    default:
        break;
    }
    // �^�C�}�[�����炷
    if (notesTimer_ > 0) notesTimer_--;
    
    // �p�����[�^��ύX
    if (notesTimer_ > 30) {
        notesPos.y -= 2.0f;
        notesSize += {0.2f, 0.2f};
        notesColor.w += 0.2f;
    }
    else {
        notesColor.w -= 0.04f;
    }
    // ���̒l�𒴂��Ȃ��悤�ɐݒ�
    if (notesPos.y < 180)       notesPos.y   = 180;
    if (notesSize.x > 1.0f)     notesSize    = { 1.0f,1.0f };
    notesColor.w = clamp(notesColor.w, 0.0f, 1.0f);
    debug::setString("notesTimer:%d", notesTimer_);
    debug::setString("notesColor.w:%f", notesColor.w);
}

void Game::decisionDraw()
{
    if (notesTimer_ > 0) {
        // �R���{�����e�L�X�g�\��
        font::textOut(6,
            notesText.str(),
            notesPos,
            notesSize,
            notesColor,
            TEXT_ALIGN::MIDDLE_RIGHT
        );
    }
}

// TODO: ���V��p
// ��������i���j
void Game::operationDraw() {
    // std::ostringstream ss1, ss2, ss3;
    // 
    // ss1 << "[W]+Enter->UpAttack";
    // 
    // // �R���{�����e�L�X�g�\��
    // font::textOut(6,
    //     ss1.str(),
    //     { 10, 70 },
    //     { 0.6f, 0.6f },
    //     { 1.0f, 1.0f, 1.0f, 1.0f },
    //     TEXT_ALIGN::LOWER_LEFT
    // );
    // ss2 << "[A]+Enter->LeftAttack";
    // 
    // // �R���{�����e�L�X�g�\��
    // font::textOut(6,
    //     ss2.str(),
    //     { 10, 90 },
    //     { 0.6f, 0.6f },
    //     { 1.0f, 1.0f, 1.0f, 1.0f },
    //     TEXT_ALIGN::LOWER_LEFT
    // );
    // 
    // ss3 << "[D]+Enter->RightAttack";
    // 
    // // �R���{�����e�L�X�g�\��
    // font::textOut(6,
    //     ss3.str(),
    //     { 10, 110 },
    //     { 0.6f, 0.6f },
    //     { 1.0f, 1.0f, 1.0f, 1.0f },
    //     TEXT_ALIGN::LOWER_LEFT
    // );
}

//******************************************************************************