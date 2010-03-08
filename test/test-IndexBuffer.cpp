#include <unittest++/UnitTest++.h>
#include <iostream>
#include <cstring>
#include "IndexBuffer.hpp"
using namespace std;
using namespace m3g;

TEST (IndexBuffer_default_variables)
{
  IndexBuffer* ibuf = new IndexBuffer;

  CHECK_EQUAL (OBJTYPE_INDEX_BUFFER, ibuf->getObjectType());
  CHECK_EQUAL (0, ibuf->getIndexCount());

  delete ibuf;
}

TEST (IndexBuffer_set_variables)
{
  IndexBuffer* ibuf = new IndexBuffer;

  int indices [10] = {50,51,52,53,54};

  ibuf->setIndices (5, indices);
  CHECK_EQUAL (5, ibuf->getIndexCount());

  memset (indices, 0, sizeof(indices));
  ibuf->getIndices (indices);

  CHECK_EQUAL (50, indices[0]);
  CHECK_EQUAL (54, indices[4]);
  CHECK_EQUAL (0, indices[5]);  // don't changed


  ibuf->setIndices (10, 100);
  CHECK_EQUAL (10, ibuf->getIndexCount());

  ibuf->getIndices (indices);
  CHECK_EQUAL (100, indices[0]);
  CHECK_EQUAL (109, indices[9]);

  delete ibuf;
  
}



