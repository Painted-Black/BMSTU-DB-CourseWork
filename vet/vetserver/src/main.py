import sys

# sys.path.append("./daemon")
# sys.path.append("./config")

from daemon.daemon import Daemon
from config.config import Config
from config.config_args import ConfigArgs

def main():
	cfg_args = ConfigArgs.fromArgs()
	cfg = Config()
	cfg.read_from_file(cfg_args.getConfigFile())
	
	d = Daemon(cfg)
	d.start()

if __name__ == "__main__":
	main()