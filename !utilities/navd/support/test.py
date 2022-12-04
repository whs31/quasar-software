
defaults = {'server_ip':'192.168.1.47', 'port':4559}

def run(parent, cfg):
    print('Run in test mode')
    parent.lat = 20;
    parent.lon = 10;
    parent.speed = 40
    parent.elv = 100
    parent.sats = 1
    
    # in progress
