#version 150 core
#extension GL_ARB_explicit_attrib_location : enable

// ���X�^���C�U����󂯎�钸�_�����̕�Ԓl
in vec3 idiff;                                      // �g�U���ˌ����x

// �t���[���o�b�t�@�ɏo�͂���f�[�^
layout (location = 0) out vec4 fc;                  // �t���O�����g�̐F

void main(void)
{
  fc = vec4(idiff, 1.0);
}
