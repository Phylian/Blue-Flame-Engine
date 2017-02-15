#pragma once
#include <BF/Graphics/Renderers/Sprite.h>
#include <BF/Graphics/Renderers/SpriteRenderer.h>
#include "Grid.h"
#include "TileMap.h"

namespace Editor
{
	class PaintTile
	{
		private:
			BF::Graphics::Renderers::SpriteRenderer& spriteRenderer;
			BF::Graphics::Renderers::Sprite currentTile;

			Grid& grid;
			Editor::TileMap& tileMap;

		public:
			PaintTile(BF::Graphics::Renderers::SpriteRenderer& spriteRenderer, Grid& grid, Editor::TileMap& tileMap);
			~PaintTile();

			void Update();
			void Render();

			void SetCurrentTile(BF::Graphics::Renderers::Sprite currentTile);
			inline const BF::Graphics::Renderers::Sprite& GetCurrentTile() const { return currentTile; }
	};
}