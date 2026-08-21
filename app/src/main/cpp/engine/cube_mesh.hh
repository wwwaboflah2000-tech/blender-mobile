#pragma once
#include "blender_godot_bridge.hh"
#include <vector>

class BlenderCubeGenerator {
public:
    static void generate_default_cube(std::vector<VertexData>& out_vertices, std::vector<uint32_t>& out_indices) {
        out_vertices.clear();
        out_indices.clear();

        // 8 نقاط تمثل زوايا مكعب بلندر الأصلي (بحجم 2x2x2)
        // الأوجه الستة مع اتجاهات الإضاءة (Normals)
        struct FaceDef { float nx, ny, nz; float v[4][3]; };
        FaceDef faces[6] = {
            // Front Face (Z+)
            { 0, 0, 1, {{-1,-1, 1}, { 1,-1, 1}, { 1, 1, 1}, {-1, 1, 1}} },
            // Back Face (Z-)
            { 0, 0,-1, {{ 1,-1,-1}, {-1,-1,-1}, {-1, 1,-1}, { 1, 1,-1}} },
            // Top Face (Y+)
            { 0, 1, 0, {{-1, 1, 1}, { 1, 1, 1}, { 1, 1,-1}, {-1, 1,-1}} },
            // Bottom Face (Y-)
            { 0,-1, 0, {{-1,-1,-1}, { 1,-1,-1}, { 1,-1, 1}, {-1,-1, 1}} },
            // Right Face (X+)
            { 1, 0, 0, {{ 1,-1, 1}, { 1,-1,-1}, { 1, 1,-1}, { 1, 1, 1}} },
            // Left Face (X-)
            {-1, 0, 0, {{-1,-1,-1}, {-1,-1, 1}, {-1, 1, 1}, {-1, 1,-1}} }
        };

        uint32_t index_offset = 0;
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 4; j++) {
                VertexData vert;
                vert.x = faces[i].v[j][0];
                vert.y = faces[i].v[j][1];
                vert.z = faces[i].v[j][2];
                vert.nx = faces[i].nx;
                vert.ny = faces[i].ny;
                vert.nz = faces[i].nz;
                vert.u = (j == 1 || j == 2) ? 1.0f : 0.0f;
                vert.v = (j >= 2) ? 1.0f : 0.0f;
                out_vertices.push_back(vert);
            }
            // ربط المثلثين لكل وجه
            out_indices.push_back(index_offset + 0);
            out_indices.push_back(index_offset + 1);
            out_indices.push_back(index_offset + 2);
            out_indices.push_back(index_offset + 0);
            out_indices.push_back(index_offset + 2);
            out_indices.push_back(index_offset + 3);
            index_offset += 4;
        }
    }
};
