#include "BlockType.hpp"

#include <iostream>

#include "../../../../../../Engine/Util/Math.hpp"

std::vector<engine::Vertex> BlockType::getVertices(glm::ivec3 localTransform, bool front, bool frontRight, bool back, bool frontLeft, bool top, bool bottom)
{
    std::vector<engine::Vertex> tempVertices;

    if (!front && !frontRight && !back && !frontLeft && !top && !bottom)
    {
        return tempVertices;
    }

    if (front && frontRight && back && frontLeft && top && bottom)
    {
        tempVertices = m_Vertices;
    }
    else
    {
        if (front)
            tempVertices.insert(tempVertices.end(), m_VerticesFrontFace.begin(), m_VerticesFrontFace.end());

        if (frontRight)
            tempVertices.insert(tempVertices.end(), m_VerticesFrontRightFace.begin(), m_VerticesFrontRightFace.end());

        if (back)
            tempVertices.insert(tempVertices.end(), m_VerticesBackFace.begin(), m_VerticesBackFace.end());

        if (frontLeft)
            tempVertices.insert(tempVertices.end(), m_VerticesFrontLeftFace.begin(), m_VerticesFrontLeftFace.end());

        if (top)
            tempVertices.insert(tempVertices.end(), m_VerticesTopFace.begin(), m_VerticesTopFace.end());

        if (top)
            tempVertices.insert(tempVertices.end(), m_VerticesBottomFace.begin(), m_VerticesBottomFace.end());
    }

    for (auto& v : tempVertices)
    {
        v.m_Position.x += localTransform.x;
        v.m_Position.y += localTransform.y;
        v.m_Position.z += localTransform.z;
    }

    return tempVertices;
}

std::vector<uint> BlockType::getIndices(uint greatestIndex, bool front, bool frontRight, bool back, bool frontLeft, bool top, bool bottom)
{
    std::vector<uint> tempIndices;

    uint faces = 0;

    if (front && frontRight && back && frontLeft && top && bottom)
    {
        tempIndices = m_Indices;
    }
    else
    {
        if (front)
            faces++;

        if (frontRight)
            faces++;

        if (back)
            faces++;

        if (frontLeft)
            faces++;

        if (top)
            faces++;

        if (top)
            faces++;

    }

    // you have to fix this

    greatestIndex++;

    for (int i = 0; i < faces; i++)
    {
        std::vector<uint> quickTempIndicesFace = m_IndicesFace;
        for (auto& q : quickTempIndicesFace)
        {
            q += (i * 4) + greatestIndex;
        }
        tempIndices.insert(tempIndices.end(), quickTempIndicesFace.begin(), quickTempIndicesFace.end());

    }

    return tempIndices;
}

std::vector<float> BlockType::createVertexPositions()
{
    return std::vector
    {
        -0.5f, -0.5f, -0.5f, //0 //front
         0.5f, -0.5f, -0.5f, //1
         0.5f, -0.5f,  0.5f, //2
        -0.5f, -0.5f,  0.5f, //3

         0.5f, -0.5f, -0.5f, //4 //front-right
         0.5f,  0.5f, -0.5f, //5
         0.5f,  0.5f,  0.5f, //6
         0.5f, -0.5f,  0.5f, //7

         0.5f,  0.5f, -0.5f, //8 //back
        -0.5f,  0.5f, -0.5f, //9
        -0.5f,  0.5f,  0.5f, //10
         0.5f,  0.5f,  0.5f, //11

        -0.5f,  0.5f, -0.5f, //12 //front-left
        -0.5f, -0.5f, -0.5f, //13
        -0.5f, -0.5f,  0.5f, //14
        -0.5f,  0.5f,  0.5f, //15

        -0.5f, -0.5f,  0.5f, //16 //top
         0.5f, -0.5f,  0.5f, //17
         0.5f,  0.5f,  0.5f, //18
        -0.5f,  0.5f,  0.5f, //19

        -0.5f,  0.5f, -0.5f, //20 //bottom
         0.5f,  0.5f, -0.5f, //21
         0.5f, -0.5f, -0.5f, //22
        -0.5f, -0.5f, -0.5f  //23
    };
}

std::vector<uint> BlockType::createIndices()
{
    return std::vector<uint>
    {
        0u, 1u, 2u, //front
        2u, 3u, 0u,

        4u, 5u, 6u, //front-right
        6u, 7u, 4u,

        8u, 9u, 10u, //back
        10u, 11u, 8u,

        12u, 13u, 14u, //front-left
        14u, 15u, 12u,

        16u, 17u, 18u, //top
        18u, 19u, 16u,

        20u, 21u, 22u, //bottom
        22u, 23u, 20u
    };
}

void BlockType::createFaces()
{
    m_VerticesFrontFace.resize(4);

    m_VerticesFrontFace.at(0) = m_Vertices.at(0);
    m_VerticesFrontFace.at(1) = m_Vertices.at(1);
    m_VerticesFrontFace.at(2) = m_Vertices.at(2);
    m_VerticesFrontFace.at(3) = m_Vertices.at(3);

    m_VerticesFrontRightFace.resize(4);

    m_VerticesFrontRightFace.at(0) = m_Vertices.at(4);
    m_VerticesFrontRightFace.at(1) = m_Vertices.at(5);
    m_VerticesFrontRightFace.at(2) = m_Vertices.at(6);
    m_VerticesFrontRightFace.at(3) = m_Vertices.at(7);

    m_VerticesBackFace.resize(4);

    m_VerticesBackFace.at(0) = m_Vertices.at(8);
    m_VerticesBackFace.at(1) = m_Vertices.at(9);
    m_VerticesBackFace.at(2) = m_Vertices.at(10);
    m_VerticesBackFace.at(3) = m_Vertices.at(11);

    m_VerticesFrontLeftFace.resize(4);
    
    m_VerticesFrontLeftFace.at(0) = m_Vertices.at(12);
    m_VerticesFrontLeftFace.at(1) = m_Vertices.at(13);
    m_VerticesFrontLeftFace.at(2) = m_Vertices.at(14);
    m_VerticesFrontLeftFace.at(3) = m_Vertices.at(15);

    m_VerticesTopFace.resize(4);

    m_VerticesTopFace.at(0) = m_Vertices.at(16);
    m_VerticesTopFace.at(1) = m_Vertices.at(17);
    m_VerticesTopFace.at(2) = m_Vertices.at(18);
    m_VerticesTopFace.at(3) = m_Vertices.at(19);

    m_VerticesBottomFace.resize(4);

    m_VerticesBottomFace.at(0) = m_Vertices.at(20);
    m_VerticesBottomFace.at(1) = m_Vertices.at(21);
    m_VerticesBottomFace.at(2) = m_Vertices.at(22);
    m_VerticesBottomFace.at(3) = m_Vertices.at(23);

    m_IndicesFace.resize(6);

    m_IndicesFace.at(0) = m_Indices.at(0);
    m_IndicesFace.at(1) = m_Indices.at(1);
    m_IndicesFace.at(2) = m_Indices.at(2);
    m_IndicesFace.at(3) = m_Indices.at(3);
    m_IndicesFace.at(4) = m_Indices.at(4);
    m_IndicesFace.at(5) = m_Indices.at(5);
}
