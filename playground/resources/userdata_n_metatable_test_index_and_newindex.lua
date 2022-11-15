sprite = Sprite.Create();

sprite:Move( 11, 22 )

sprite.x = 77
sprite.y = 88
--sprite.y() -- is call __index and then boom

sprite:Move()

temp_x = sprite.x