sprite = Sprite.Create();

sprite:Draw() -- is same Sprite.Draw( sprite )
sprite:Move( 1, 2 ) -- is same Sprite.Move( sprite, 1, 2 )
sprite:Draw()
sprite:Move( 2, 4 )
sprite:Draw()