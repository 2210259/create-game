#pragma once
//******************************************************************************
//
//      bg.h
//
//******************************************************************************

//==============================================================================
//
//      BG�N���X
//
//==============================================================================


class BG
{
public:
    //------< �萔 >------------------------------------------------------------
    static const int WINDOW_W = 1280;                   // �E�C���h�E�̕�
    static const int WINDOW_H = 720;                    // �E�C���h�E�̍���
    static const int CLIENT_W = 1280;                   // �N���C�A���g�̈�̕�
    static const int CLIENT_H = 720;                    // �N���C�A���g�̈�̍���

    static const int CHIP_SIZE = 64;                    // %���Z�q���g�p���邽��int�^���g�p����
    static const int LOOP_X = CLIENT_W / CHIP_SIZE + (CLIENT_W % CHIP_SIZE ? 2 : 1);
    static const int LOOP_Y = CLIENT_H / CHIP_SIZE + (CLIENT_H % CHIP_SIZE ? 2 : 1);

    static const int CHIP_NUM_X = 20;                   // �}�b�v�̉������̃`�b�v��
    static const int CHIP_NUM_Y = 12;                   // �}�b�v�̏c�����̃`�b�v��
    static const int CHIP_NUM_PER_LINE = 6;             // �}�b�v�`�b�v��1��8��
    static const int CHIP_LINE_NUM = 2;                 // �}�b�v�`�b�v���S�s

    static constexpr float CHIP_SIZE_F = static_cast<float>(CHIP_SIZE);
    static constexpr float WIDTH = static_cast<float>(CHIP_NUM_X * CHIP_SIZE);  // �}�b�v�̕��i�h�b�g�j
    static constexpr float HEIGHT = static_cast<float>(CHIP_NUM_Y * CHIP_SIZE); // �}�b�v�̍����i�h�b�g�j
    static constexpr float SCROLL_MERGIN_X = 240.f;     // ���̐��l����ʒ[�ɋ߂Â�����X�N���[������i���j
    static constexpr float SCROLL_MERGIN_Y = 160.f;     // ���̐��l����ʒ[�ɋ߂Â�����X�N���[������i�c�j
    static constexpr float ADJUST_Y = 0.25f;            // �����蔻��ł̈ʒu�����p�i�c�j
    static constexpr float ADJUST_X = 0.025f;           // �����蔻��ł̈ʒu�����p�i���j

    // �n�`�iTerrain�j�̑���
    enum class TR_ATTR
    {
        TR_NONE = -1,   // -1:�����Ȃ�
        ALL_BLOCK,      //  0:�l���u���b�N
        UPPER_BLOCK,    //  1:�ゾ���u���b�N
        HASHIGO,        //  2:�͂���
    };

    // �I�u�W�F�N�g�iBack�j�̑���
    enum class OB_ATTR
    {
        BG_NONE = -1,   // -1:�����Ȃ�
        NORMAL,         //  0:���ʁi���ɉ����Ȃ��j
        WATER,          //  1:�����i��R���󂯂�j
    };

private:
    // �n�`�`�b�v�e�N�X�`���̊e�����̑������`����
    const TR_ATTR terrainAttr[CHIP_LINE_NUM * CHIP_NUM_PER_LINE] = {
        TR_ATTR::TR_NONE,   TR_ATTR::TR_NONE,   TR_ATTR::TR_NONE,   TR_ATTR::ALL_BLOCK,   TR_ATTR::ALL_BLOCK, TR_ATTR::ALL_BLOCK,
        TR_ATTR::ALL_BLOCK, TR_ATTR::ALL_BLOCK, TR_ATTR::ALL_BLOCK, TR_ATTR::ALL_BLOCK, TR_ATTR::ALL_BLOCK,   TR_ATTR::ALL_BLOCK,
    };

    // �I�u�W�F�N�g�`�b�v�e�N�X�`���̊e�����̑������`����
    const OB_ATTR ObjectAttr[CHIP_LINE_NUM * CHIP_NUM_PER_LINE] = {
        OB_ATTR::NORMAL,      OB_ATTR::NORMAL,      OB_ATTR::NORMAL,      OB_ATTR::NORMAL,      OB_ATTR::NORMAL,    OB_ATTR::NORMAL,
        OB_ATTR::BG_NONE,     OB_ATTR::BG_NONE,     OB_ATTR::BG_NONE,     OB_ATTR::BG_NONE,     OB_ATTR::BG_NONE,   OB_ATTR::BG_NONE,
    };

    //------< �ϐ� >------------------------------------------------------------
    VECTOR2 scroll;                                         // ���ݕ\������Ă��鍶��̒n�_�̍��W
    OBJ2D* player_;

    char terrain[CHIP_NUM_Y][CHIP_NUM_X];                   // �n�`�f�[�^
    char object[CHIP_NUM_Y][CHIP_NUM_X];                    // �I�u�W�F�N�g�f�[�^

public:
    BG();
    ~BG();

    // ������
    void init(OBJ2D* player);

    // �X�V
    void update();

    // �`��
    void drawObject();                                      // �I�u�W�F�N�g�`��
    void drawTerrain();                                     // �n�`�`��

    // �X�N���[���ʒu�擾
    float getScrollX() { return scroll.x; }
    float getScrollY() { return scroll.y; }
    const VECTOR2& getScrollPos() { return scroll; }

    // �����蔻��
    // ������
    bool isFloor(float, float, float);          // ���ɂ߂荞��ł��邩
    void mapHoseiDown(OBJ2D*);                  // �������␳����

    // �����
    bool isCeiling(float, float, float);        // �V��ɂ������Ă��邩
    void mapHoseiUp(OBJ2D*);                    // ������␳����

    // ������
    bool isWall(float, float, float);           // �������ɕǂɂ߂荞��ł��邩
    void mapHoseiRight(OBJ2D*);                 // �E�����␳����
    void mapHoseiLeft(OBJ2D*);                  // �������␳����

    // ��R
    float calcResistance(const OBJ2D*, float);
    OB_ATTR getObjectAttr(const VECTOR2&);
    float getTeikou(OB_ATTR, float);
    bool isInWater(const OBJ2D*);

    TR_ATTR getTerrainAttr(const VECTOR2&);

private:
    // �N���A
    void clear();

    // �}�b�v�f�[�^�̃��[�h
    bool loadMapData(const char[][CHIP_NUM_X], char[][CHIP_NUM_X]);

    // BG�ATerrain���ʂ̕`��֐�
    void draw(int, char[][CHIP_NUM_X]);  // �`�揈���i�X���[�Y�ȃX�N���[���j

    // �}�b�v�X�N���[���p
    void scrollMap();

    bool isHitDown(float, float);
    bool isHitAll(float, float);
    bool isUpperQuater(float);
    int getData(char[][BG::CHIP_NUM_X], const VECTOR2&);
};

//******************************************************************************
