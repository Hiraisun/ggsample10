#version 410 core

// 光源
const vec4 pl = vec4(3.0, 4.0, 5.0, 1.0);           // 位置
const vec3 ldiff  = vec3(1.0, 1.0, 1.0);            // 拡散反射成分の強度

// 材質
const vec3 kdiff  = vec3(0.8, 0.8, 0.8);            // 拡散反射係数

// 頂点属性
layout (location = 0) in vec4 pv;                   // ローカル座標系の頂点位置
layout (location = 1) in vec4 nv;                   // 頂点の法線ベクトル

// 変換行列
uniform mat4 mw;                                    // 視点座標系への変換行列
uniform mat4 mc;                                    // クリッピング座標系への変換行列
uniform mat4 mg;                                    // 法線ベクトルの変換行列

// 球面調和解析
const float k1 = 0.429043;
const float k2 = 0.511664;
const float k3 = 0.743125;
const float k4 = 0.886227;
const float k5 = 0.247708;
uniform vec3 sh[10];                                // 球面調和係数

// ラスタライザに送る頂点属性
out vec3 idiff;                                     // 拡散反射光強度

void main(void)
{
  vec4 p = mw * pv;                                 // 視点座標系の頂点の位置
  vec3 l = normalize((pl * p.w - p * pl.w).xyz);    // 光線ベクトル
  vec3 n = normalize((mg * nv).xyz);                // 法線ベクトル


  // 球面調和解析による拡散反射光強度の計算
  vec3 e1 = k1 * sh[8] * (n.x * n.x - n.y * n.y);
  vec3 e2 = k3 * sh[6] * n.z * n.z;
  vec3 e3 = k4 * sh[0];
  vec3 e4 = k5 * sh[6];
  vec3 e5 = 2 * k1 * (sh[4] * n.x * n.y + sh[7] * n.x * n.z + sh[5] * n.y * n.z);
  vec3 e6 = 2 * k2 * (sh[3] * n.x + sh[1] * n.y + sh[2] * n.z);

  vec3 e =  e1 + e2 + e3 - e4 + e5 + e6;
  idiff = (kdiff * e);

  gl_Position = mc * pv;
}
