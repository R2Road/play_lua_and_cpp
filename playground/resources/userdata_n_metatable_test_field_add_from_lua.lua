sprite = Sprite.Create();

sprite:Move( 11, 22 )
sprite:Draw()

sprite.x = 77
sprite.y = 88
sprite:Draw()

sprite.z = 100
sprite.x = sprite.z

sprite:Draw()

temp_x = sprite.x