// �E�B���h�E�֘A�̏���
#include "Window.h"

// �V�F�[�_�[�֘A�̏���
#include "shader.h"

// �W�����C�u����
#include <cmath>
#include <memory>

// �A�j���[�V�����̎����i�b�j
const double cycle(10.0);

//
// SH �W���e�[�u��
//
#include "shcoeff.h"

//
// ���C���v���O����
//
int main(int argc, const char * argv[])
{
  // �E�B���h�E���쐬����
  Window window("ggsample10");

  // �w�i�F���w�肷��
  glClearColor(0.1f, 0.2f, 0.3f, 0.0f);

  // �B�ʏ�����L���ɂ���
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  // �v���O�����I�u�W�F�N�g�̍쐬
  const GLuint program(loadProgram("simple.vert", "pv", "simple.frag", "fc"));

  // uniform �ϐ��̃C���f�b�N�X�̌����i������Ȃ���� -1�j
  const GLint mwLoc(glGetUniformLocation(program, "mw"));
  const GLint mcLoc(glGetUniformLocation(program, "mc"));
  const GLint mgLoc(glGetUniformLocation(program, "mg"));
  const GLint shLoc(glGetUniformLocation(program, "sh"));

  // �r���[�ϊ��s��� mv �ɋ��߂�
  const GgMatrix mv(ggLookat(0.0f, 1.0f, 2.3f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f));

  // �}�`�f�[�^�̍쐬
  const std::unique_ptr<const GgElements> object(ggElementsObj("bunny.obj"));

  // �o�ߎ��Ԃ̃��Z�b�g
  glfwSetTime(0.0);

  // �E�B���h�E���J���Ă���Ԃ���Ԃ��`�悷��
  while (window.shouldClose() == GL_FALSE)
  {
    // ��ʏ���
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // �V�F�[�_�v���O�����̎g�p�J�n
    glUseProgram(program);

    // �����̌v��
    const float t(static_cast<float>(fmod(glfwGetTime(), cycle) / cycle));

    // SH �W���e�[�u���̔ԍ�
    const int shtable(static_cast<int>(nshcoeff * t) % nshcoeff);

    // ���f���r���[�ϊ��s�� (���� t �ɂ��ƂÂ���]�A�j���[�V����)
    const GgMatrix mw(mv.rotateY(12.56637f * t));

    // �@���ϊ��s��
    const GgMatrix mg(mw.normal());

    // ���e�ϊ��s��
    const GgMatrix mp(ggPerspective(0.5f, window.getAspect(), 1.0f, 15.0f));

    // ���f���r���[�E���e�ϊ�
    const GgMatrix mc(mp * mw);

    // uniform �ϐ���ݒ肷��
    glUniformMatrix4fv(mwLoc, 1, GL_FALSE, mw.get());
    glUniformMatrix4fv(mcLoc, 1, GL_FALSE, mc.get());
    glUniformMatrix4fv(mgLoc, 1, GL_FALSE, mg.get());
    glUniform3fv(shLoc, 9, *shcoeff[shtable]);

    // �}�`�̕`��
    object->draw();

    // �V�F�[�_�v���O�����̎g�p�I��
    glUseProgram(0);

    // �J���[�o�b�t�@�����ւ��ăC�x���g�����o��
    window.swapBuffers();
  }

  return 0;
}
