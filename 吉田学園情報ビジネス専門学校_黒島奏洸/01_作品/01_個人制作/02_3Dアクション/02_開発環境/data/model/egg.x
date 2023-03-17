xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 40;
 0.00000;0.10724;-0.00000;,
 6.85164;2.67787;3.95579;,
 0.00000;2.67787;7.91159;,
 0.00000;0.10724;-0.00000;,
 6.85164;2.67787;-3.95580;,
 0.00000;0.10724;-0.00000;,
 -0.00000;2.67787;-7.91159;,
 0.00000;0.10724;-0.00000;,
 -6.85164;2.67787;-3.95580;,
 0.00000;0.10724;-0.00000;,
 -6.85164;2.67787;3.95579;,
 0.00000;0.10724;-0.00000;,
 0.00000;2.67787;7.91159;,
 11.08618;6.43233;6.40061;,
 0.00000;6.43233;12.80122;,
 11.08618;6.43233;-6.40061;,
 -0.00000;6.43233;-12.80122;,
 -11.08618;6.43233;-6.40061;,
 -11.08618;6.43233;6.40061;,
 0.00000;6.43233;12.80122;,
 11.08618;18.23895;6.40061;,
 0.00000;18.23895;12.80122;,
 11.08618;18.23895;-6.40061;,
 -0.00000;18.23895;-12.80122;,
 -11.08618;18.23895;-6.40061;,
 -11.08618;18.23895;6.40061;,
 0.00000;18.23895;12.80122;,
 6.85164;27.31403;3.95580;,
 0.00000;27.31403;7.91159;,
 6.85164;27.31403;-3.95579;,
 -0.00000;27.31403;-7.91159;,
 -6.85164;27.31403;-3.95579;,
 -6.85164;27.31403;3.95580;,
 0.00000;27.31403;7.91159;,
 0.00000;31.59176;0.00000;,
 0.00000;31.59176;0.00000;,
 0.00000;31.59176;0.00000;,
 0.00000;31.59176;0.00000;,
 0.00000;31.59176;0.00000;,
 0.00000;31.59176;0.00000;;
 
 30;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;9,10,8;,
 3;11,12,10;,
 4;2,1,13,14;,
 4;1,4,15,13;,
 4;4,6,16,15;,
 4;6,8,17,16;,
 4;8,10,18,17;,
 4;10,12,19,18;,
 4;14,13,20,21;,
 4;13,15,22,20;,
 4;15,16,23,22;,
 4;16,17,24,23;,
 4;17,18,25,24;,
 4;18,19,26,25;,
 4;21,20,27,28;,
 4;20,22,29,27;,
 4;22,23,30,29;,
 4;23,24,31,30;,
 4;24,25,32,31;,
 4;25,26,33,32;,
 3;28,27,34;,
 3;27,29,35;,
 3;29,30,36;,
 3;30,31,37;,
 3;31,32,38;,
 3;32,33,39;;
 
 MeshMaterialList {
  1;
  30;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.505098;0.800000;0.749804;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  31;
  -0.000000;-1.000000;0.000000;,
  -0.000000;-0.886613;0.462511;,
  0.400546;-0.886613;0.231256;,
  0.400547;-0.886613;-0.231256;,
  -0.000000;-0.886613;-0.462511;,
  -0.400547;-0.886613;-0.231256;,
  -0.400547;-0.886613;0.231256;,
  -0.000000;-0.460945;0.887429;,
  0.768536;-0.460944;0.443714;,
  0.768536;-0.460944;-0.443715;,
  -0.000000;-0.460944;-0.887429;,
  -0.768536;-0.460944;-0.443714;,
  -0.768536;-0.460944;0.443714;,
  0.190383;0.322009;0.927397;,
  0.707958;0.322009;0.628574;,
  0.898340;0.322009;-0.298822;,
  0.190382;0.322009;-0.927397;,
  -0.707958;0.322009;-0.628574;,
  -0.898340;0.322009;0.298822;,
  -0.000000;0.714842;0.699286;,
  0.605600;0.714842;0.349643;,
  0.605600;0.714842;-0.349643;,
  -0.000000;0.714842;-0.699286;,
  -0.605600;0.714842;-0.349643;,
  -0.605600;0.714842;0.349643;,
  -0.000000;1.000000;-0.000000;,
  1.000000;0.000000;-0.000000;,
  0.500000;0.000000;-0.866025;,
  -0.500000;0.000000;-0.866025;,
  -1.000000;0.000000;0.000000;,
  -0.500000;0.000000;0.866025;;
  30;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,1,6;,
  4;1,2,8,7;,
  4;2,3,9,8;,
  4;3,4,10,9;,
  4;4,5,11,10;,
  4;5,6,12,11;,
  4;6,1,7,12;,
  4;7,8,14,13;,
  4;8,9,15,26;,
  4;9,10,16,27;,
  4;10,11,17,28;,
  4;11,12,18,29;,
  4;12,7,30,30;,
  4;13,14,20,19;,
  4;14,15,21,20;,
  4;15,16,22,21;,
  4;16,17,23,22;,
  4;17,18,24,23;,
  4;18,13,19,24;,
  3;19,20,25;,
  3;20,21,25;,
  3;21,22,25;,
  3;22,23,25;,
  3;23,24,25;,
  3;24,19,25;;
 }
 MeshTextureCoords {
  40;
  0.083333;0.000000;,
  0.166667;0.200000;,
  0.000000;0.200000;,
  0.250000;0.000000;,
  0.333333;0.200000;,
  0.416667;0.000000;,
  0.500000;0.200000;,
  0.583333;0.000000;,
  0.666667;0.200000;,
  0.750000;0.000000;,
  0.833333;0.200000;,
  0.916667;0.000000;,
  1.000000;0.200000;,
  0.166667;0.400000;,
  0.000000;0.400000;,
  0.333333;0.400000;,
  0.500000;0.400000;,
  0.666667;0.400000;,
  0.833333;0.400000;,
  1.000000;0.400000;,
  0.166667;0.600000;,
  0.000000;0.600000;,
  0.333333;0.600000;,
  0.500000;0.600000;,
  0.666667;0.600000;,
  0.833333;0.600000;,
  1.000000;0.600000;,
  0.166667;0.800000;,
  0.000000;0.800000;,
  0.333333;0.800000;,
  0.500000;0.800000;,
  0.666667;0.800000;,
  0.833333;0.800000;,
  1.000000;0.800000;,
  0.083333;1.000000;,
  0.250000;1.000000;,
  0.416667;1.000000;,
  0.583333;1.000000;,
  0.750000;1.000000;,
  0.916667;1.000000;;
 }
}
