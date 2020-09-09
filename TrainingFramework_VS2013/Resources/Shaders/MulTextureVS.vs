//attribute vec4 a_posL;
//uniform mat4 u_mvpMatrix;
//varying vec4 v_pos;

//void main(void)
//{
//	gl_Position = u_mvpMatrix * a_posL;
//	v_pos = a_posL;
//}

attribute vec4 a_posL;
attribute vec4 a_color;
attribute vec4 a_position;
attribute vec2 a_uv;
varying vec4 v_color;
uniform mat4 u_mvpMatrix;
varying vec2 v_uv;

void main()
{
gl_Position = u_mvpMatrix * a_posL;
v_uv = a_uv;
}