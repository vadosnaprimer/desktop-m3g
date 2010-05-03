

#ifndef __RUBY_M3G_HPP__
#define __RUBY_M3G_HPP__

void register_Graphics3D (VALUE rb_cGraphics3D);
void register_Graphics3D (VALUE rb_cGraphics3D);
void register_Loader (VALUE rb_cLoader);
void register_AnimationController (VALUE rb_cAnimationController);
void register_AnimationTrack (VALUE rb_cAnimationTrack);
void register_Appearance (VALUE rb_cAppearance);
void register_Background (VALUE rb_cBackground);
void register_CompositingMode (VALUE rb_cCompositingMode);
void register_Fog (VALUE rb_cFog);
void register_Group (VALUE rb_cGroup);
void register_Image2D (VALUE rb_cImage2D);
void register_IndexBuffer (VALUE rb_cIndexBuffer);
void register_TriangleStripArray (VALUE rb_cTriangleStripArray);
void register_KeyframeSequence (VALUE rb_cKeyframeSequence);
void register_Material (VALUE rb_cMaterial);
void register_PolygonMode (VALUE rb_cPolygonMode);
void register_Transformable (VALUE rb_cTransformable);
void register_Node (VALUE rb_cNode);
void register_Camera (VALUE rb_cCamera);
void register_Group (VALUE rb_cGroup);
void register_World (VALUE rb_cWorld);
void register_Light (VALUE rb_cLight);
void register_Mesh (VALUE rb_cMesh);
void register_MorphingMesh (VALUE rb_cMorphingMesh);
void register_SkinnedMesh (VALUE rb_cSkinnedMesh);
void register_Sprite3D (VALUE rb_cSprite3D);
void register_Texture2D (VALUE rb_cTexture2D);
void register_VertexArray (VALUE rb_cVertexArray);
void register_VertexBuffer (VALUE rb_cVertexBuffer);
void register_RayIntersection (VALUE rb_cRayIntersection);
void register_Transform (VALUE rb_cTransform);

void register_ActiveInterval (VALUE rb_cActiveInterval);
void register_Crop (VALUE rb_cCrop);
void register_ImageMode (VALUE rb_cImageMode);
void register_Projection (VALUE rb_cProjection);
void register_Viewport (VALUE rb_cViewport);
void register_TextureCoord2D (VALUE rb_cTextureCoord2D);


#endif
