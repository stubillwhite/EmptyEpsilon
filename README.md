![EmptyEpsilon logo](https://raw.githubusercontent.com/daid/EmptyEpsilon/master/resources/logo_full.png)

This is a LARP version of the game [Empty Epsilon](http://emptyepsilon.org/). The aim here is to add screens and feature to the vanilla game to increase immersion and gm-oriented action.

Contributing
===========

Some general contribution rules (based of vanilla game):

1.  This project is a dictatorship. Yes, it's open source, but we'd much rather spend time on building what we like than arguing with people.

2.  Be precise when filing issues. Explain why you posted the issue, what you expect, what is happening, why is your feature worth the time to develop it, what operating system is affected, etc. Unclear issues are subject to rule 1 with extreme prejudice.

3.  Despite the above two, we very much value input, feedback, and suggestions from people playing EmptyEpsilon. If you have ideas or want to donate beer, drop us a line.



# Hardware Configuration

The basis of hardware configuration is `hardware.ini` file. It is used to configure lights, sounds, smoke and such systems to be triggered by events in the game or changes of the game state. For example illuminate the room of blue color when shields are up or blink lights when your ship takes hull damage.

This article shows the basics of configuration but doesn't cover DMX device setup.

## Table of Contents

- [`hardware.ini`](https://github.com/daid/EmptyEpsilon/wiki/DMX-Configuration#hardwareini)
- [Sections](https://github.com/daid/EmptyEpsilon/wiki/DMX-Configuration#sections)
  - [`[hardware]`](https://github.com/daid/EmptyEpsilon/wiki/DMX-Configuration#hardware)
  - [`[channels]`](https://github.com/daid/EmptyEpsilon/wiki/DMX-Configuration#channels)
  - [`[state]`](https://github.com/daid/EmptyEpsilon/wiki/DMX-Configuration#state)
  - [`[event]`](https://github.com/daid/EmptyEpsilon/wiki/DMX-Configuration#event)
  - [`condition`/`trigger` values (DMX cues)](https://github.com/daid/EmptyEpsilon/wiki/DMX-Configuration#conditiontrigger-values)
- [`hardware.ini example`](https://github.com/daid/EmptyEpsilon/wiki/Dmx-configuration-example-(hardware.ini))


## `hardware.ini`

The file is not created by game so it needs to be created manually. The table below shows where `hardware.ini` must be created.

| Operation system | Location of `hardware.ini`                                           |
|------------------|----------------------------------------------------------------------|
| Linux, Mac OS X  | `~/.emptyepsilon/hardware.ini`                                       |
| Windows          | `hardware.ini` is in the same directory where `EmptyEpsilon.exe` is. |


## Sections
`hardware.ini` consists of sections. Each section starts with `[...]` and ends with an empty line. Comment lines start with `#`.

### `[hardware]`

You can have multiple hardware definitions and thus more than just one hardware device connected.
 Below are all supported device types:
* `DMX512SerialDevice`
* `EnttecDMXProDevice`
* `sACNDevice`
* `uDMXDevice`
* `OSCDevice`
* `PhilipsHueDevice`
* `VirtualOutputDevice`

`VirtualOutputDevice` is for debugging as it draws device blocks on top of the game. 

Port is the serial port where your dmx device is connected. 
For using `VirtualOutputDevice` port name doesn't need to be valid.
The serial port can be defined with a "pseudo" name. For example in windows you can say `port = \Device\USBSER@@@` to connect to any Arduino connected to the system, no matter the port number.
You can also have multiple hardware definitions.

You can also define how many channels are available for device via `channel` -parameter. This defaults to `512` if not defined.

```
[hardware]
device = DMX512SerialDevice
port = COM1

[hardware]
device = DMX512SerialDevice
port = COM2
channels = 32
```

#### OSCDevice

The OSC device will allow OSC messages to be generated and sent over UDP to an OSC server. When a floating point value is sent to a numbered DMX channel, it is sent directly as a single floating point value to the corresponding OSC address. 

The OSC device is confugured using the following directives:
* `channels` - the number of channels that will be transmitted to the OSC endpoint (defaults to 512)
* `server_address` - the IP address of the OSC server to send the messages to (defaults to `127.0.0.1`)
* `port_number` - the UDP port number to send the OSC packets to (defaults to 53000)
* `send_data_only_if_changed` - tells the OSC device only to update the server if the data has changed - rather than updating whenever data is updated from the game engine (defaults to 'no' / 'false') - you can set this to 'yes', 'y', 'true' or '1' to enable it.
* `address_prefix` - the OSC address prefix that is used to generate the OSC messages. The channel number will be appended to the OSC address prefix for each of the channels. This defaults to `/emptyepsilon/channel/`, so the OSC addresses will be `/emptyepsilon/channel/1`, `/emptyepsilon/channel/2`, `/emptyepsilon/channel/3`, etc. You can also omit the trailing `/` if you want, and the addresses would be named `/emptyepsilon/channel1`, `/emptyepsilon/channel2`, `/emptyepsilon/channel3`, etc.
* `channel_addresses` - you can specify individual channel addresses in a comma-separated format. These will override the addresses generated from the address prefix. For example using a value of `/ee/anadddress, /ee/anotheradddress, /ee/thirdadddress` would override the first three channel addresses with the specified addresses. 

### `[channels]`

To use a channel a name must be assigned to it. In this case we're configuring three lamps. `4channelSpot` represents generic RGB device that needs four channels, one for intensity and three for each color channel. `MainCabinLights` and `WarningLights` need one channel.

If a device needs multiple channels supply a comma separated list instead of a single value. See the example below.

There are 512 channels available to use.

```
[channels]
MainCabinLights  = 1
WarningLights    = 2

# This device has four channels (intensity, red, blue, green)
4channelSpot = 10, 11, 12, 13
```

#### `[state & event]`
States and events blocks defines what our previously defined DMX devices should do when 
different actions are taken in game. 

For all `state` and `event` sections, you can set a parameter `ship_number`. This is a zero-indexed number that represents which ship the `state` or `event` section will apply to. The list of ships is as follows: 0 = main ship being run by this instance of EE, 1 = first extra ship created in the scenario, 2 = second extra ship, etc.
If `ship_number` is not set, then it will default to zero, which is the main ship being run by the instance.

#### value
DMX protocol defines that channel can have values ranging from 0 to 255.
We can configure this value in three ways.

1. Float (default) 
- value can be any float point number between 0 and 1. 
- Values above 1 are treated as 1.
- Easy to set something forexample in half power `value = 0.5`
- This is the only format that will work with OSC output

2. Hexadecimal number
- Two digit hexadecimal number. For example: `$AF`, `$3F` , `$2B`. 
- Hexadecimals need to be prefixed with `$` as `#` is already reserved for comments in configuration file.  
- Very usable for configuring colors as they are many times displayed as 6 digit hex numbers. For example `#F5F686` id hex value for yellow color and we can split this value to three groups of two digit hex values and map these to our DMX devices RGB channels. Like `$F5, $F6, $86` 

3. as decimal numbers
- Values between 0 and 255 are accepted. 
- Decimal numbers needs to be wrapped in square brakets `[100]`.
- Nice and clean way to trigger that specific channel on your DMX devices. 
 
#### `[state]`

To simply turn lights on give a value to some channel. The `value` is float.

```
[state]
condition = Always       # The simplest condition
target = MainCabinLight  # Channel
value = 1                # value as float between 0..1
```

To change `4channelSpot` output simply define comma separated list of values. The following example makes the device output purple color at 50% intensity.

```
[state]
condition = Always
target = 4channelSpot
value = 0.5, $ff, $00, $ff  # intensity as float and (red, green, blue) as hex values
```

`condition` can of course be more complex. This section set's cabin light to 50% when the game is not yet started.

```
[state]
condition = HasShip == 0
target = MainCabinLight
value = 0.5
```

It's possible to light up warning lights when the ship has taken quite a lot of damage.

```
[state]
condition = Hull < 50
target = WarningLight
value = 0.5
```

State can also have effects. three different effects are supported, `Glow`, `Blink`, and `Variable`.

`Glow`
value goes from `min_value` to `max_value` in `time`, then back down.
```
[state]
condition = ShieldsUp
target = WarningLights
effect = Glow               # Effect name
min_value = 0.3
max_value = 1
time = 1.0                  # Seconds
```

`Blink`
value turns on (255) for `on_time`, then off for `off_time`
```
[state]
condition = Hull < 50
target = WarningLights
effect = Blink          # Effect name
on_time = 0.1           # Seconds
off_time = 0.1          # Seconds
```

`Variable`
value follows a condition value, mapping values between `min_input` and `max_input` to `min_output` and `max_output`
```
[state]
condition = HasShip
target = ShieldsLevel
effect = variable
input = Shield0, Shield1
min_input = 0
max_input = 100
min_output = 0.0
max_output = 1.0
```

#### `[event]`

Events are one time only type of things. For example when the ship takes a hit lights blink.

`trigger` is a parameter to look for. When it changes the event fires. Before `trigger` it's possible to have operator `<` or `>`. Couple of examples:

```
[event]
trigger = HasShip
target = WarningLights
runtime = 1.0             # Seconds
value = 1.0

[event]
trigger = Energy          # Energy level changes
target = MainCabinLights
runtime = 1.0
value = 1.0

[event]
trigger = <Hull           # Hull takes damage
target = WarningLights
runtime = 1.0
value = 1.0

[event]
trigger = <FrontShield   # Front shield absorbs damage
target = WarningLights
runtime = 0.25
value = 1.0
```

#### `condition`/`trigger` values (DMX cues)

Conditions for states, or triggers for events can be based of the following properties. All these properties are based on the current ship that you are flying.

| Property                     | Description                                                              | Value     |
|-------------------------------|--------------------------------------------------------------------------|-----------|
| `Always`                      | Always active                                                            | `1.0`     |
| `HasShip`                     | 1 when you have a ship or it's selected. Otherwise 0.                    | `0` / `1` |
| `Hull`                        | 0 to 100 hull percentage.                                                | `0..100`  |
| `FrontShield`                 | 0 to 100 shield percentage.                                              | `0..100`  |
| `RearShield`                  | 0 to 100 shield percentage.                                              | `0..100`  |
| `Shield0`                     | 0 to 100 shield percentage. Same as Front shield.                        | `0..100`  |
| `Shield1`                     | 0 to 100 shield percentage. Same as Rear shield.                         | `0..100`  |
| `Shield[2-7]`                 | 0 to 100 shield percentage. Additional shields, not yet supported.       | `0..100`  |
| `Energy`                      | 0 to 100 energy percentage your ship has.                                | `0..100`  |
| `ShieldsUp`                   | 1 when your shields are up, 0 when they are down.                        | `0` / `1` |
| `Impulse`                     | Amount of impulse output in -1 (full reverse) to 1 (full forward)        | `-1..1`   |
| `Warp`                        | Amount of warp, from 0 to 4                                              | `0..4`    |
| `Docking`                     | While docking, or docked, this is 1. Else it is 0.                       | `0` / `1` |
| `Docked`                      | If we are actually docked, this is 1. Else it is 0.                      | `0` / `1` |
| `InNebula`                    | If we are in a nebula, this is 1, else it is 0.                          | `0` / `1` |
| `IsJammed`                    | If we are being jammed, this is 1. Else it is 0.                         | `0` / `1` |
| `Jumping`                     | If we are counting down to jump, this is 1. Else it is 0.                | `0` / `1` |
| `Jumped`                      | After jump this is 1 for 1 second.                                       | `0` / `1` |
| `Alert`                       | True if alert is yellow or red, 0 if no alert.                           | `0` / `1` |
| `YellowAlert`                 | True if alert level is yellow.                                           | `0` / `1` |
| `RedAlert`                    | True if alert level is red.                                              | `0` / `1` |
| `TubeLoaded[0-16]`            | If we have a weapon loaded in this tube it is 1. Else it is 0.           | `0` / `1` |
| `TubeLoading[0-16]`           | When loading this tube, this property is 1. Else it is 0.                | `0` / `1` |
| `TubeUnloading[0-16]`         | When unloading this tube, this property is 1. Else it is 0.              | `0` / `1` |
| `TubeUnloading[0-16]`         | When unloading this tube, this property is 1. Else it is 0.              | `0` / `1` |
| `TubeFiring[0-16]`            | When firing a tube, this property is 1. Else it is 0.                    | `0` / `1` |
| `SelfDestruct`                | When Self Destruct is activated, this property is 1. Else it is 0.       | `0` / `1` |
| `SelfDestructCountdown`       | Self destruct countdown is happening, this property is 1. Else it is 0.  | `0` / `1` |
| `ReactorHealth`               | 0 to 100 Reactor health level                                            | `0..100`  |
| `ReactorPower`                | 0 to 100 Reactor Power Level                                             | `0..100`  |
| `ReactorHeat`                 | 0 to 100 Reactor heat level                                              | `0..100`  |
| `ReactorCoolant`              | 0 to 100 Reactor coolant level                                           | `0..100`  |
| `ReactorHacked`               | 0 to 100 Reactor hacked level                                            | `0..100`  |
| `BeamWeaponsHealth`           | 0 to 100 Beam Weapons health level                                       | `0..100`  |
| `BeamWeaponsPower`            | 0 to 100 Beam Weapons power level                                        | `0..100`  |
| `BeamWeaponsHeat`             | 0 to 100 Beam Weapons heat level                                         | `0..100`  |
| `BeamWeaponsCoolant`          | 0 to 100 Beam Weapons coolant level                                      | `0..100`  |
| `BeamWeaponsHacked`           | 0 to 100 Beam Weapons hacked level                                       | `0..100`  |
| `MissileSystemHealth`         | 0 to 100 Missile System health level                                     | `0..100`  |
| `MissileSystemPower`          | 0 to 100 Missile System power level                                      | `0..100`  |
| `MissileSystemHeat`           | 0 to 100 Missile System heat level                                       | `0..100`  |
| `MissileSystemCoolant`        | 0 to 100 Missile System coolant level                                    | `0..100`  |
| `MissileSystemHacked`         | 0 to 100 Missile System hacked level                                     | `0..100`  |
| `ManeuveringHealth`           | 0 to 100 Maneuvering health level                                        | `0..100`  |
| `ManeuveringPower`            | 0 to 100 Maneuvering power level                                         | `0..100`  |
| `ManeuveringHeat`             | 0 to 100 Maneuvering heat level                                          | `0..100`  |
| `ManeuveringCoolant`          | 0 to 100 Maneuvering coolant level                                       | `0..100`  |
| `ManeuveringHacked`           | 0 to 100 Maneuvering hacked level                                        | `0..100`  |
| `ImpulseEnginesHealth`        | 0 to 100 Impulse Engines health level                                    | `0..100`  |
| `ImpulseEnginesPower`         | 0 to 100 Impulse Engines power level                                     | `0..100`  |
| `ImpulseEnginesHeat`          | 0 to 100 Impulse Engines heat level                                      | `0..100`  |
| `ImpulseEnginesCoolant`       | 0 to 100 Impulse Engines coolant level                                   | `0..100`  |
| `ImpulseEnginesHacked`        | 0 to 100 Impulse Engines hacked level                                    | `0..100`  |
| `WarpDriveHealth`             | 0 to 100 Warp Drive health level                                         | `0..100`  |
| `WarpDrivePower`              | 0 to 100 Warp Drive power level                                          | `0..100`  |
| `WarpDriveHeat`               | 0 to 100 Warp Drive heat level                                           | `0..100`  |
| `WarpDriveCoolant`            | 0 to 100 Warp Drive coolant level                                        | `0..100`  |
| `WarpDriveHacked`             | 0 to 100 Warp Drive hacked level                                         | `0..100`  |
| `JumpDriveHealth`             | 0 to 100 Jump Drive health level                                         | `0..100`  |
| `JumpDrivePower`              | 0 to 100 Jump Drive power level                                          | `0..100`  |
| `JumpDriveHeat`               | 0 to 100 Jump Drive heat level                                           | `0..100`  |
| `JumpDriveCoolant`            | 0 to 100 Jump Drive coolant level                                        | `0..100`  |
| `JumpDriveHacked`             | 0 to 100 Jump Drive hacked level                                         | `0..100`  |
| `FrontShieldGeneratorHealth`  | 0 to 100 Front Shield health level                                       | `0..100`  |
| `FrontShieldGeneratorPower`   | 0 to 100 Front Shield power level                                        | `0..100`  |
| `FrontShieldGeneratorHeat`    | 0 to 100 Front Shield heat level                                         | `0..100`  |
| `FrontShieldGeneratorCoolant` | 0 to 100 Front Shield coolant level                                      | `0..100`  |
| `FrontShieldGeneratorHacked`  | 0 to 100 Front Shield hacked level                                       | `0..100`  |
| `RearShieldGeneratorHealth`   | 0 to 100 Rear Shield health level                                        | `0..100`  |
| `RearShieldGeneratorPower`    | 0 to 100 Rear Shield power level                                         | `0..100`  |
| `RearShieldGeneratorHeat`     | 0 to 100 Rear Shield heat level                                          | `0..100`  |
| `RearShieldGeneratorCoolant`  | 0 to 100 Rear Shield coolant level                                       | `0..100`  |
| `RearShieldGeneratorHacked`   | 0 to 100 Rear Shield hacked level                                        | `0..100`  |
 

(If you need more options. Feel free to file an issue)


# Build Process

## Cross compilation on linux

Install Ubuntu 20.04 (must not be later version because it will use recent versions of mingw gcc/gpp which have errors with this codebase)

```
sudo apt update
sudo apt upgrade
sudo apt install wget cmake build-essential git unzip zip p7zip-full mingw-w64 ninja-build libsdl2-dev libfreetype-dev
mkdir workspace
cd workspace
git clone --branch larp-v2-hardware https://github.com/tombull/EmptyEpsilon.git
git clone https://github.com/tdelc/SeriousProton.git
cd SeriousProton
git reset --hard b068a01550d11ddeb57b9437eb193361f24458c6
cd ..
cd EmptyEpsilon
mkdir _build_win32
cd _build_win32
cmake .. -G Ninja -DSERIOUS_PROTON_DIR=../../SeriousProton -DCMAKE_TOOLCHAIN_FILE=../cmake/mingw.toolchain -DCMAKE_BUILD_TYPE=RelWithDebInfo
cmake --build . --target package
```

This doesn't work.

## Windows Build

* Fresh installation of Windows 10 Pro
* Install git for windows, Notepad++, 7-zip
* Install Visual Studio 2019 Community Edition (Include C++ development features)
* Choose a folder for your source control repos and build, we'll call this {reposRootFolder}
* Open Visual Studio Community Edition by and when prompted to open a project, clone https://github.com/tombull/EmptyEpsilon.git into a folder {reposRootFolder}\EmptyEpsilon
* Download https://www.sfml-dev.org/files/SFML-2.5.1-windows-vc15-32-bit.zip and unzip the contents into {reposRootFolder}\externals
* Open Visual Studio Command Prompt from the 'Tools' menu
* Change directory to {reposRootFolder} and execute the following commands
```
git checkout larp-v2-hardware
cd ..
git clone https://github.com/tdelc/SeriousProton.git
cd SeriousProton
git reset --hard b068a01550d11ddeb57b9437eb193361f24458c6
cd ..
cmake -E make_directory {reposRootFolder}\build
cd build
cmake ../EmptyEpsilon -G "Visual Studio 16 2019" -A Win32 -DCMAKE_BUILD_TYPE=RelWithDebInfo -DSFML_ROOT="../externals/SFML-2.5.1" -DSERIOUS_PROTON_DIR="../SeriousProton"
cmake --build . --config RelWithDebInfo --target package
```

This doesn't work.

## Cross compilation on linux with older linker

Install Ubuntu 18.04 (must not be later version because it will use recent versions of mingw gcc/gpp which have errors with this codebase)

```
sudo apt update
sudo apt upgrade
sudo apt install wget cmake build-essential git unzip zip p7zip-full mingw-w64 ninja-build libsdl2-dev libfreetype-dev
mkdir workspace
cd workspace
git clone --branch larp-v2-hardware https://github.com/tombull/EmptyEpsilon.git
git clone https://github.com/tdelc/SeriousProton.git
cd SeriousProton
git reset --hard b068a01550d11ddeb57b9437eb193361f24458c6
cd ..
cd EmptyEpsilon
mkdir _build_win32
cd _build_win32
cmake .. -G Ninja -DSERIOUS_PROTON_DIR=../../SeriousProton -DCMAKE_TOOLCHAIN_FILE=../cmake/mingw.toolchain -DCMAKE_BUILD_TYPE=RelWithDebInfo
cmake --build . --target package
```

This works!