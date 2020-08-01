#include "Chunk.h"

namespace Minecraft
{
	Chunk::Chunk(const glm::vec3 chunk_position) : p_Position(chunk_position), p_MeshState(ChunkMeshState::Unbuilt), p_ChunkState(ChunkState::Ungenerated)
	{
		// Initialize all the blocks in the chunk to be air blocks

		memset(&p_ChunkContents, BlockType::Air, CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z);
		memset(&p_ChunkLightInformation, 0, CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z);
	}

	Chunk::~Chunk()
	{
		
	}

	void Chunk::SetBlock(BlockType type, const glm::vec3& position)
	{
		Block b;
		b.p_BlockType = type;

		p_ChunkContents.at(position.x).at(position.y).at(position.z) = b;
	}

	int Chunk::GetSunlightAt(int x, int y, int z)
	{
		// Shift four bits so you only get the sunlight info
		// Then & that with 15 (0xF)
		return (p_ChunkLightInformation[x][y][z] >> 4) & 0xF;
	}

	int Chunk::GetTorchLightAt(int x, int y, int z)
	{
		return (p_ChunkLightInformation[x][y][z]) & 0xF;
	}

	void Chunk::SetSunlightAt(int x, int y, int z, int light_val)
	{
		p_ChunkLightInformation[x][y][z] = (p_ChunkLightInformation[x][y][z] & 0xF) | (light_val << 4);
	}

	void Chunk::SetTorchLightAt(int x, int y, int z, int light_val)
	{
		p_ChunkLightInformation[x][y][z] = (p_ChunkLightInformation[x][y][z] & 0xF0) | light_val;
	}

	void Chunk::Construct()
	{
		m_ChunkMesh.ConstructMesh(this, p_Position);
		p_MeshState = ChunkMeshState::Built;
	}

	ChunkMesh* Chunk::GetChunkMesh()
	{
		return &m_ChunkMesh;
	}

	Block* Chunk::GetBlock(int x, int y, int z)
	{
		return &p_ChunkContents[x][y][z];
	}
}