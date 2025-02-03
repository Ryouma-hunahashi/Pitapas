#include "CAnimation.h"

void CAnimation::Update()
{
    // �e�[�u���A�j���[�V�����c���߂�ꂽ���ԂōĐ������邽�߂̃f�[�^
    // ���e�[�u���c�����̖ړI�̂��߂ɍ��ꂽ�f�[�^�̏W�܂�
    int animTable[][80] =
    {
        // �����A�j���[�V�������Ȃ��p�^�[��
        { 0, -1 },

        // �v���C���[�A�j���[�V����
        {0,1,2,3,4,5,6,7,-1},

        // �v���C���[���S�A�j���[�V����
        {0,1,2,3,4,5,6,7,-3},

        // �G�t�F�N�g�p�O�`�P�P�܂ōĐ�
        { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, -2 },

        // �G�t�F�N�g�p�O�`�P�X�܂ōĐ�
        {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,-2},

        // 
        {0,1,2,3,4,5, 6,7,8,9,10, 11,12,13,14,15, 16,17,18,19,20, 21,22,23,24,25, 26,27,28,29,30, 31,32,33,34,35, -2},
        {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,-1}
    };

    // �\��������R�}ID���擾
    int animID = animTable[animPattern][(int)animCounter];
    
    // uv�T�C�Y�����߂�
    uv.x = animID % static_cast<int>(split.x) / (split.x);
    uv.y = animID / static_cast<int>(split.x) / (split.y);


    // �Đ������ǂ�������
    if (isPlaying)
    {
        // �A�j���[�V�����̃J�E���^�[��i�߂�
        animCounter += animSpeed;

        // �ŏ��ɖ߂鏈��
        if (animTable[animPattern][(int)animCounter] == -1)// -1�����[�v�̍��}
        {
            animCounter = 0.0f;
        }
        // ��~�����鏈��
        else if (animTable[animPattern][(int)animCounter] == -2)// -2���~�߂鍇�}
        {
            animCounter = 0.0f;
            isPlaying = false;
        }
        else if (animTable[animPattern][(int)animCounter] == -3) // �v���C���[���S���Ɏg�p
        {
            animCounter = 7;
            isPlaying = false;
        }
    }
}

CDirectX::FLOAT_XY CAnimation::GetUV()
{
    return uv;
}

void CAnimation::SetPattern(int pattern)
{
    animPattern = pattern;
}

void CAnimation::SetAnimCounter(float count)
{
    animCounter = count;
}
