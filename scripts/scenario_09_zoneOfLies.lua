-- Name: Zone of Lies
-- Description: Why, EmptyEpsilon? Who hurt you?
-- Type: Basic

require("utils.lua")

function init()
    -- This sort of seems to work
    starfighter1 = PlayerSpaceship():setTemplate("Interceptor")
        :setPosition(-30000, 0):setRotationMaxSpeed(14.8)
        :setWarpDrive(true):setWarpSpeed(1000, 1000)
        :setCallSign("interceptor")
        :commandImpulse(100)

    -- This doesn't
    starfighter2 = PlayerSpaceship():setTemplate("UCS Skirmish Class Frigate")
        :setPosition(-30000, 1000)
        :setCallSign("frigate")
        :commandImpulse(100)

    -- Old Talavaar model
    starfighter3 = PlayerSpaceship():setTemplate("UCS Talavaar Class Destroyer")
        :setPosition(-30000, 2000)
        :setCallSign("talavaar")
        :commandImpulse(100)

    -- New shuttle
    starfighter4 = PlayerSpaceship():setTemplate("UCS Havock Shuttle")
        :setPosition(-30000, 3000)
        :setCallSign("shuttle")
        :commandImpulse(100)

    -- New Takanami
    starfighter5 = PlayerSpaceship():setTemplate("UCS Hoplite Class Destroyer")
        :setPosition(-30000, 4000)
        :setCallSign("takanami")
        :commandImpulse(100)

    -- scenarioShuttle = PlayerSpaceship():setPosition(-30000, 1000) --:setWarpDrive(true):setWarpSpeed(1000.00)
    -- -- scenarioShuttle = PlayerSpaceship():setFaction("Independent"):setPosition(-35000, 1000):setWarpDrive(true):setWarpSpeed(1000.00)
    -- -- scenarioShuttle = PlayerSpaceship():setFaction("Independent"):setPosition(444667, 444852):setWarpDrive(true):setWarpSpeed(1000.00)
    -- scenarioShuttle:setTemplate("UCS Havock Shuttle"):setCallSign("UCS Havock Shuttle") --:setFaction("Independent")
    -- scenarioShuttle:commandImpulse(100)

    -- scenarioShuttle = PlayerSpaceship()
    --     :setPosition(-35000, 1000) -- Dust
    --     -- :setPosition(-30000, 1000) -- No dust >_<
    --     :setTemplate("UCS Havock Shuttle")
    --     :setCallSign("scenarioShuttle")
    --     :commandImpulse(100)

    -- -- New shuttle
    -- starfighter5 = PlayerSpaceship()
    --     :setPosition(-30000, 2000)
    --     :setTemplate("UCS Havock Shuttle")
    --     :setCallSign("shuttle")
    --     :commandImpulse(100)

    starfighters = {
        starfighter1,
        starfighter2,
        starfighter3,
        starfighter4,
        starfighter5,
        scenarioShuttle
    }
    asteroidCircleList = {}

    addGMFunction(
        "Set warp",
        function()
            for aIdx, aObj in ipairs(starfighters) do
                aObj:commandWarp(1)
            end
        end
    )

    addGMFunction(
        "Set impulse",
        function()
            for aIdx, aObj in ipairs(starfighters) do
                aObj:commandWarp(0)
                aObj:commandImpulse(100)
            end
        end
    )

    addGMFunction(
        "Generate asteroids",
        function()
            generateAsteroids()
        end
    )
end

function cleanup()
end

function update(delta)
    moveAsteroids()
end

function generateAsteroids()
    local asteroidCount = 40
    local centerX, centerY = 0, 0
    local asteroidSpeed = 20
    local initialRadius = 4000

    for n = 0, asteroidCount - 1 do
        local angle = 360 / asteroidCount * n
        local dx, dy = vectorFromAngle(angle, initialRadius)
        local size = 20

        local asteroid = Asteroid():setPosition(centerX + dx, centerY + dy):setSize(size)
        asteroid.angle = angle
        asteroid.travel = asteroidSpeed + random(0, 10)

        table.insert(asteroidCircleList, asteroid)
    end
end

function moveAsteroids()
    local finalRadius = 20000

    for aIdx, aObj in ipairs(asteroidCircleList) do
        if aObj:isValid() then
            if distanceFromCenter(aObj, 0, 0) >= finalRadius then
                aObj:destroy()
            else
                local x, y = aObj:getPosition()
                local dx, dy = vectorFromAngle(aObj.angle, aObj.travel)
                aObj:setPosition(x + dx, y + dy)
            end
        else
            table.remove(asteroidCircleList, aIdx)
        end
    end
end

function vectorFromAngle(angle, length)
    return math.cos(angle / 180 * math.pi) * length, math.sin(angle / 180 * math.pi) * length
end

function distanceFromCenter(obj, centerX, centerY)
    local objX, objY = obj:getPosition()
    local dx, dy = (objX - centerX), (objY - centerY)
    return math.sqrt(dx * dx + dy * dy)
end
