#include <unittest++/UnitTest++.h>
#include <iostream>
#include <cstring>
#include <GL/gl.h>
#include "m3g/VertexArray.hpp"
#include "m3g/BoneWeight.hpp"
using namespace std;
using namespace m3g;


/**
 * ベースとなるVertexArrayと変形後のVertexArrayが同じ型である必要はない。
 * ここではわざとshort型とfloat型を使用している。
 */
TEST (VertexArray_setSkinning_1)
{
    VertexArray* base    = new VertexArray (2, 3, 2);
    VertexArray* skinned = new VertexArray (2, 3, 4);
    short base_values[6] = {0,1,2, 3,4,5};

    base->set (0, 2, base_values);

    vector<vector<BoneWeight> > bone_indices;

    vector<BoneWeight> bone_weights_v0;
    bone_weights_v0.push_back (BoneWeight(0, 100));
    bone_weights_v0.push_back (BoneWeight(1, 0));
    bone_indices.push_back (bone_weights_v0);

    vector<BoneWeight> bone_weights_v1;
    //bone_weights_v1.push_back (BoneWeight(0, 0));
    bone_weights_v1.push_back (BoneWeight(1, 100));
    bone_indices.push_back (bone_weights_v1);
    
    
    vector<Matrix> matrix_palette;
    
    matrix_palette.push_back (Matrix(1,0,0,0,
                                     0,2,0,0,
                                     0,0,3,0,
                                     0,0,0,1));
    matrix_palette.push_back (Matrix(1,0,0,1,
                                     0,1,0,2,
                                     0,0,1,3,
                                     0,0,0,1));

    //base->print_raw_data (cout);
    skinned->setSkinning (base, bone_indices, matrix_palette);
    //skinned->print_raw_data (cout);

    float skinned_values[6];

    skinned->get (0, 2, skinned_values);

    CHECK_EQUAL (0, skinned_values[0]);
    CHECK_EQUAL (2, skinned_values[1]);
    CHECK_EQUAL (6, skinned_values[2]);
    CHECK_EQUAL (4, skinned_values[3]);
    CHECK_EQUAL (6, skinned_values[4]);
    CHECK_EQUAL (8, skinned_values[5]);
    
}

TEST (VertexArray_setSkinning_2)
{
    VertexArray* base    = new VertexArray (2, 3, 2);
    VertexArray* skinned = new VertexArray (2, 3, 4);
    short base_values[6] = {0,1,2, 3,4,5};

    base->set (0, 2, base_values);

    vector<vector<BoneWeight> > bone_indices;

    vector<BoneWeight> bone_weights_v0;
    bone_weights_v0.push_back (BoneWeight(0, 50));
    bone_weights_v0.push_back (BoneWeight(1, 50));
    bone_indices.push_back (bone_weights_v0);

    vector<BoneWeight> bone_weights_v1;
    bone_weights_v1.push_back (BoneWeight(0, 50));
    bone_weights_v1.push_back (BoneWeight(1, 50));
    bone_indices.push_back (bone_weights_v1);
    
    
    vector<Matrix> matrix_palette;
    
    matrix_palette.push_back (Matrix(1,0,0,0,
                                     0,2,0,0,
                                     0,0,3,0,
                                     0,0,0,1));
    matrix_palette.push_back (Matrix(1,0,0,1,
                                     0,1,0,2,
                                     0,0,1,3,
                                     0,0,0,1));

    //base->print_raw_data (cout);
    skinned->setSkinning (base, bone_indices, matrix_palette);
    //skinned->print_raw_data (cout);

    float skinned_values[6];

    skinned->get (0, 2, skinned_values);

    CHECK_EQUAL (0.5f, skinned_values[0]);
    CHECK_EQUAL (2.5f, skinned_values[1]);
    CHECK_EQUAL (5.5f, skinned_values[2]);
    CHECK_EQUAL (3.5f, skinned_values[3]);
    CHECK_EQUAL (7.0f, skinned_values[4]);
    CHECK_EQUAL (11.5f, skinned_values[5]);
}

/**
 * ベースおよびターゲットの型は同じである必要はない。
 * ここではわざとchar,short,float型を混在させている。
 */
TEST (VertexArray_setMorping)
{
    VertexArray* base    = new VertexArray (2, 3, 2);  // short型
    VertexArray* target0 = new VertexArray (2, 3, 1);  // char型
    VertexArray* target1 = new VertexArray (2, 3, 4);  // float型
    VertexArray* morphed = new VertexArray (2, 3, 4);  // float型
    short  base_values[6]    = {0,1,2, 3,4,5};
    char   target0_values[6] = {10,11,12, 13,14,15};
    float  target1_values[6] = {20,21,22, 23,24,25};

    base   ->set (0, 2, base_values);
    target0->set (0, 2, target0_values);
    target1->set (0, 2, target1_values);

    vector<const VertexArray*> targets;
    targets.push_back (target0);
    targets.push_back (target1);

    vector<float> weights (2);
    float morphed_values[6];

    weights[0] = 0;
    weights[1] = 0;
    morphed->setMorphing (base, targets, weights);
    //morphed->print_raw_data (cout) << "\n";
    morphed->get (0, 2, morphed_values);

    CHECK_EQUAL (0.f, morphed_values[0]);
    CHECK_EQUAL (1.f, morphed_values[1]);
    CHECK_EQUAL (2.f, morphed_values[2]);
    CHECK_EQUAL (3.f, morphed_values[3]);
    CHECK_EQUAL (4.f, morphed_values[4]);
    CHECK_EQUAL (5.f, morphed_values[5]);


    weights[0] = 1;
    weights[1] = 0;
    morphed->setMorphing (base, targets, weights);
    //morphed->print_raw_data (cout) << "\n";
    morphed->get (0, 2, morphed_values);

    CHECK_EQUAL (10.f, morphed_values[0]);
    CHECK_EQUAL (11.f, morphed_values[1]);
    CHECK_EQUAL (12.f, morphed_values[2]);
    CHECK_EQUAL (13.f, morphed_values[3]);
    CHECK_EQUAL (14.f, morphed_values[4]);
    CHECK_EQUAL (15.f, morphed_values[5]);


    weights[0] = 0;
    weights[1] = 1;
    morphed->setMorphing (base, targets, weights);
    //morphed->print_raw_data (cout) << "\n";
    morphed->get (0, 2, morphed_values);

    CHECK_EQUAL (20.f, morphed_values[0]);
    CHECK_EQUAL (21.f, morphed_values[1]);
    CHECK_EQUAL (22.f, morphed_values[2]);
    CHECK_EQUAL (23.f, morphed_values[3]);
    CHECK_EQUAL (24.f, morphed_values[4]);
    CHECK_EQUAL (25.f, morphed_values[5]);


    weights[0] = 0.5;
    weights[1] = 0.5;
    morphed->setMorphing (base, targets, weights);
    //morphed->print_raw_data (cout) << "\n";
    morphed->get (0, 2, morphed_values);

    CHECK_EQUAL (15.f, morphed_values[0]);
    CHECK_EQUAL (16.f, morphed_values[1]);
    CHECK_EQUAL (17.f, morphed_values[2]);
    CHECK_EQUAL (18.f, morphed_values[3]);
    CHECK_EQUAL (19.f, morphed_values[4]);
    CHECK_EQUAL (20.f, morphed_values[5]);

    

}


