-- lua initialization for headlcikder

print("LUA Loaded")

local time = 0

function update(deltaTime)
	time = time + deltaTime
end

function draw()
	local x = 2
	local y = 1
	local z = -1
	local height = 1
	local width = 1
	local length = 1
	-- drawCube(x, y, z, height, width, length)
end

-- enemy position
local x = 0
local y = 0.05
local z = 0

local x_cos_time = 2
local x_cos_bounce = 1.05

local y_cos_time = 8
local y_cos_bounce = 0.02

local z_cos_time = 0
local z_cos_bounce = 1.05

function draw_Enemy()
	-- bounce
	drawEnemy(
		x + math.sin(time * x_cos_time) * x_cos_bounce,
		y + math.cos(time * y_cos_time) * y_cos_bounce,
		z + math.sin(time * z_cos_time) * z_cos_bounce
	)
end

function draw_EnemyHealthBar()
	drawHealthBar(
		x + math.sin(time * x_cos_time) * x_cos_bounce,
		y + 2.4 + math.cos(time * y_cos_time) * y_cos_bounce,
		z + math.sin(time * z_cos_time) * z_cos_bounce
	)
end
