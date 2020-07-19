import readline
import cmd
import os
import sys
import re
import time

from os import listdir
from os.path import isfile, join

class Client:
    __CONFIG_PATH = "/srv/nfsroot/root/configs/"
    POSITIONS = [
        "none", "helms", "weapons", "engineering", "science", "relay",
        "tactical", "engineering+", "operations",
        "single",
        "damageControl", "powerManagement", "databaseView",
        "altRelay", "commsOnly", "shipLog", "tractorView", "dronePilot", "dockMaster"
    ]

    def __init__(self, mac, ip):
        if os.path.isdir("test/"):
            self.__CONFIG_PATH = "test/"
        self.__mac_all = mac
        self.__mac = mac.replace(":", "")
        self.__ip = ip
        self.__name = "None"
        self.__auto_connect = False
        self.__ship = ""
        self.__station = ""
        self.__connected = "No"
        try:
            f = open(self.getIniFilename(), "rt")
        except IOError:
            pass
        else:
            for line in f:
                if '#' in line:
                    line = line[:line.find("#")]
                if not '=' in line:
                    continue
                key, value = map(str.strip, line.strip().split("=", 1))
                if key == "instance_name":
                    self.__name = value
                elif key == "autoconnect":
                    position = int(value)
                    if position <= 0:
                        self.__auto_connect = False
                    else:
                        self.__auto_connect = True
                        self.__station = self.POSITIONS[position]
                elif key == "autoconnectship":
                    self.__ship = value
            f.close()
    
    def getMac(self):
        return self.__mac

    def getMacAll(self):
        return self.__mac_all

    def getIp(self):
        return self.__ip
    
    def getName(self):
        return self.__name
    
    def isConnected(self):
        clients = ClientDatabase().getWithName(self.__name)
        if len(clients) == 0:
            return "No"
        ip = clients[0].getIp()
        connexion = os.system("ping -c 2 -f -w 3 %s > /dev/null 2>&1" % (ip))
        if connexion == 0:
            return "Yes"
        else:
            return "No"

    def setName(self, name):
        self.__name = name
        self.replaceInIni("instance_name", name)
    
    def setPosition(self, position):
        idx = None
        for pos in self.POSITIONS:
            if position.lower() == pos.lower():
                idx = self.POSITIONS.index(pos)
        if idx is None:
            print("Unknown position: [%s], possible position: %s" % (position, ', '.join(self.POSITIONS)))
            return
        self.replaceInIni("autoconnect", idx)
    
    def getIniFilename(self):
        return os.path.join(self.__CONFIG_PATH, "%s.ini" % self.__mac)
    
    def replaceInIni(self, key, value):
        lines = []
        try:
            f = open(self.getIniFilename(), "rt")
            for line in f:
               if line.split("=")[0].strip() != key:
                   lines.append(line)
            f.close()
        except IOError:
            pass
        lines.append("%s=%s\n" % (key, value))
        f = open(self.getIniFilename(), "wt")
        for line in lines:
            f.write(line)
        f.close()

    def runOnClient(self, command):
        os.system("ssh -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null %s '%s'" % (self.getIp(), command))

    def wakeUpClient(self):
        os.system("etherwake %s" % (self.getMacAll()))

    def __repr__(self):
        if self.__auto_connect:
            return "%s %s [%s] (%s) %s" % (self.__mac, self.__name, self.__station, self.__ship, self.__connected)
        return "%s %s %s" % (self.__mac, self.__name, self.isConnected())

class ClientDatabase:
    __LEASES_FILE = "/var/lib/misc/dnsmasq.leases"

    def __init__(self):
        if os.path.isfile("test/dnsmasq.leases"):
            self.__LEASES_FILE = "test/dnsmasq.leases"
    
    def getClients(self):
        clients = []
        for line in open(self.__LEASES_FILE, "rt"):
            mac_address = line.strip().split(" ")[1]
            ip_address = line.strip().split(" ")[2]
            clients.append(Client(mac_address, ip_address))
        return clients
    
    def getWithName(self, name):
        if name == "":
            return []
        clients = self.getClients()
        if name == "all":
            return clients
        if name == "bug":
            result = []
            for client in clients:
                if client.isConnected() == "No":
                    result.append(client)
            return result
        expr = "^"
        for char in name:
            if char == "*":
                expr += ".*"
            elif char == "?":
                expr += "."
            else:
                expr += char
        expr += "$"
        result = []
        for client in clients:
            if re.match(expr, client.getMac()) != None:
                result.append(client)
            elif re.match(expr, client.getName()) != None:
                result.append(client)
        return result

class ConfigsDatabase:
    __CONFIGS_PATH = "/srv/nfsroot/root/configs/"
    
    def getConfigs(self):
        configs = []
        for f in listdir(self.__CONFIGS_PATH):
            mac_address = f.replace(".ini", "")
            mac_address = mac_address[0:2]+":"+mac_address[2:4]+":"+mac_address[4:6]+":"+mac_address[6:8]+":"+mac_address[8:10]+":"+mac_address[10:12]
            configs.append(Client(mac_address, ""))
        return configs
    
    def getWithName(self, name):
        if name == "":
            return []
        configs = self.getConfigs()
        if name == "all":
            return configs
        if name == "bug":
            result = []
            for config in configs:
                if config.isConnected() == "No":
                    result.append(config)
            return result
        expr = "^"
        for char in name:
            if char == "*":
                expr += ".*"
            elif char == "?":
                expr += "."
            else:
                expr += char
        expr += "$"
        result = []
        for config in configs:
            if re.match(expr, config.getMac()) != None:
                result.append(config)
            elif re.match(expr, config.getName()) != None:
                result.append(config)
        return result
    
class ConfigCmd(cmd.Cmd):
    def __init__(self, client_database, config_database):
        cmd.Cmd.__init__(self)
        self.__client_database = client_database
        self.__config_database = config_database
    
    def _getClient(self, args):
        clients = self.__client_database.getWithName(args)
        if len(clients) == 1:
            return clients[0]
        print("Failed to find client with name '%s'." % (args))
        return None

    def _getClients(self, args):
        clients = self.__client_database.getWithName(args)
        if len(clients) > 0:
            return clients
        print("Failed to find clients with name '%s'." % (args))
        return []
        
    def _getConfig(self, args):
        configs = self.__config_database.getWithName(args)
        if len(configs) == 1:
            return configs[0]
        print("Failed to find configs with name '%s'." % (args))
        return None

    def _getConfigs(self, args):
        configs = self.__config_database.getWithName(args)
        if len(configs) > 0:
            return configs
        print("Failed to find configs with name '%s'." % (args))
        return []
    
    def do_list_clients(self, args):
        'List all the clients known to the server.'
        for client in self.__client_database.getClients():
            print(client)

    def do_list_configs(self, args):
        'List all the configs file recorded in the server.'
        for config in self.__config_database.getConfigs():
            print(config)
                
    def do_edit(self, args):
        'Directly edit a configuration file for a certain client, will create a new file if none exists.'
        client = self._getClient(args)
        if not client:
            return
        os.system("nano \"%s\"" % (client.getIniFilename()))
    
    def complete_edit(self, text, line, begidx, endidx):
        result = []
        for client in self.__client_database.getClients():
            if client.getMac().startswith(text):
                result.append(client.getMac())
            if client.getName().startswith(text):
                result.append(client.getName())
        return result

    def do_setname(self, args):
        'Set a name of a machine'
        args = args.split(" ", 1)
        client = self._getClient(args[0])
        if not client:
            return
        client.setName(args[1])
    
    def complete_setname(self, text, line, begidx, endidx):
        return self.complete_edit(text, line, begidx, endidx)

    def do_setposition(self, args):
        'Set the autoconnect position of a client'
        args = args.split(" ", 1)
        client = self._getClient(args[0])
        if not client:
            return
        client.setPosition(args[1])
    
    def complete_setname(self, text, line, begidx, endidx):
        return self.complete_edit(text, line, begidx, endidx)

    def do_exec(self, args):
        'Execute any command trough SSH on one or more clients.'
        args = args.split(" ", 1)
        for client in self._getClients(args[0]):
            client.runOnClient(args[1])

    def do_switch_web(self, args):
        'Switch client to Chromium web browser.'
        for client in self._getClients(args):
            client.runOnClient("systemctl stop emptyepsilon")
            time.sleep(3)
            client.runOnClient("systemctl start chromium")

    def do_switch_ee(self, args):
        'Switch client to Empty Epsilon.'
        for client in self._getClients(args):
            client.runOnClient("systemctl stop chromium")
            time.sleep(3)
            client.runOnClient("systemctl start emptyepsilon")

    def complete_exec(self, text, line, begidx, endidx):
        return self.complete_edit(text, line, begidx, endidx)

    def do_set(self, args):
        'Set any option to one or more clients.'
        args = args.split(" ", 2)
        for client in self._getClients(args[0]):
            client.replaceInIni(args[1], args[2])

    def complete_set(self, text, line, begidx, endidx):
        return self.complete_edit(text, line, begidx, endidx)

    def do_reboot(self, args):
        for client in self._getClients(args):
            client.runOnClient("reboot")

    def do_shutdown(self, args):
        for client in self._getClients(args):
            client.runOnClient("shutdown -h now")

    def complete_reboot(self, text, line, begidx, endidx):
        return self.complete_edit(text, line, begidx, endidx)

    def do_restart(self, args):
        for client in self._getClients(args):
            client.runOnClient("systemctl restart emptyepsilon.service")

    def complete_restart(self, text, line, begidx, endidx):
        return self.complete_edit(text, line, begidx, endidx)

    def do_wakeup(self, args):
        for client in self._getConfigs(args):
            client.wakeUpClient()
    
    def do_monitoring(self, args):
        try:
            while True:
                os.system('clear')
                print("Monitoring of all configs recorded on this server")
                print("Press Ctrl-C to exit")
                self.do_list_configs(self)
                time.sleep(5)
        except KeyboardInterrupt:
            pass
            
    def do_exit(self, args):
        'Exit the configuration editor.'
        return True

if len(sys.argv) > 1:
    ConfigCmd(ClientDatabase(),ConfigsDatabase()).onecmd(" ".join(sys.argv[1:]))
else:
    ConfigCmd(ClientDatabase(),ConfigsDatabase()).cmdloop()
