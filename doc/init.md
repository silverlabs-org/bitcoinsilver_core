Sample init scripts and service configuration for bitcoin_silverd
==========================================================

Sample scripts and configuration files for systemd, Upstart and OpenRC
can be found in the contrib/init folder.

    contrib/init/bitcoin_silverd.service:    systemd service unit configuration
    contrib/init/bitcoin_silverd.openrc:     OpenRC compatible SysV style init script
    contrib/init/bitcoin_silverd.openrcconf: OpenRC conf.d file
    contrib/init/bitcoin_silverd.conf:       Upstart service configuration file
    contrib/init/bitcoin_silverd.init:       CentOS compatible SysV style init script

Service User
---------------------------------

All three Linux startup configurations assume the existence of a "bitcoin_silver" user
and group.  They must be created before attempting to use these scripts.
The macOS configuration assumes bitcoin_silverd will be set up for the current user.

Configuration
---------------------------------

Running bitcoin_silverd as a daemon does not require any manual configuration. You may
set the `rpcauth` setting in the `bitcoin_silver.conf` configuration file to override
the default behaviour of using a special cookie for authentication.

This password does not have to be remembered or typed as it is mostly used
as a fixed token that bitcoin_silverd and client programs read from the configuration
file, however it is recommended that a strong and secure password be used
as this password is security critical to securing the wallet should the
wallet be enabled.

If bitcoin_silverd is run with the "-server" flag (set by default), and no rpcpassword is set,
it will use a special cookie file for authentication. The cookie is generated with random
content when the daemon starts, and deleted when it exits. Read access to this file
controls who can access it through RPC.

By default the cookie is stored in the data directory, but it's location can be overridden
with the option '-rpccookiefile'.

This allows for running bitcoin_silverd without having to do any manual configuration.

`conf`, `pid`, and `wallet` accept relative paths which are interpreted as
relative to the data directory. `wallet` *only* supports relative paths.

For an example configuration file that describes the configuration settings,
see `share/examples/bitcoin_silver.conf`.

Paths
---------------------------------

### Linux

All three configurations assume several paths that might need to be adjusted.

    Binary:              /usr/bin/bitcoin_silverd
    Configuration file:  /etc/bitcoin_silver/bitcoin_silver.conf
    Data directory:      /var/lib/bitcoin_silverd
    PID file:            /var/run/bitcoin_silverd/bitcoin_silverd.pid (OpenRC and Upstart) or
                         /run/bitcoin_silverd/bitcoin_silverd.pid (systemd)
    Lock file:           /var/lock/subsys/bitcoin_silverd (CentOS)

The PID directory (if applicable) and data directory should both be owned by the
bitcoin_silver user and group. It is advised for security reasons to make the
configuration file and data directory only readable by the bitcoin_silver user and
group. Access to bitcoin_silver-cli and other bitcoin_silverd rpc clients can then be
controlled by group membership.

NOTE: When using the systemd .service file, the creation of the aforementioned
directories and the setting of their permissions is automatically handled by
systemd. Directories are given a permission of 710, giving the bitcoin_silver group
access to files under it _if_ the files themselves give permission to the
bitcoin_silver group to do so (e.g. when `-sysperms` is specified). This does not allow
for the listing of files under the directory.

NOTE: It is not currently possible to override `datadir` in
`/etc/bitcoin_silver/bitcoin_silver.conf` with the current systemd, OpenRC, and Upstart init
files out-of-the-box. This is because the command line options specified in the
init files take precedence over the configurations in
`/etc/bitcoin_silver/bitcoin_silver.conf`. However, some init systems have their own
configuration mechanisms that would allow for overriding the command line
options specified in the init files (e.g. setting `BITCOIN_SILVERD_DATADIR` for
OpenRC).

### macOS

    Binary:              /usr/local/bin/bitcoin_silverd
    Configuration file:  ~/Library/Application Support/Bitcoin_Silver/bitcoin_silver.conf
    Data directory:      ~/Library/Application Support/Bitcoin_Silver
    Lock file:           ~/Library/Application Support/Bitcoin_Silver/.lock

Installing Service Configuration
-----------------------------------

### systemd

Installing this .service file consists of just copying it to
/usr/lib/systemd/system directory, followed by the command
`systemctl daemon-reload` in order to update running systemd configuration.

To test, run `systemctl start bitcoin_silverd` and to enable for system startup run
`systemctl enable bitcoin_silverd`

NOTE: When installing for systemd in Debian/Ubuntu the .service file needs to be copied to the /lib/systemd/system directory instead.

### OpenRC

Rename bitcoin_silverd.openrc to bitcoin_silverd and drop it in /etc/init.d.  Double
check ownership and permissions and make it executable.  Test it with
`/etc/init.d/bitcoin_silverd start` and configure it to run on startup with
`rc-update add bitcoin_silverd`

### Upstart (for Debian/Ubuntu based distributions)

Upstart is the default init system for Debian/Ubuntu versions older than 15.04. If you are using version 15.04 or newer and haven't manually configured upstart you should follow the systemd instructions instead.

Drop bitcoin_silverd.conf in /etc/init.  Test by running `service bitcoin_silverd start`
it will automatically start on reboot.

NOTE: This script is incompatible with CentOS 5 and Amazon Linux 2014 as they
use old versions of Upstart and do not supply the start-stop-daemon utility.

### CentOS

Copy bitcoin_silverd.init to /etc/init.d/bitcoin_silverd. Test by running `service bitcoin_silverd start`.

Using this script, you can adjust the path and flags to the bitcoin_silverd program by
setting the BITCOIN_SILVERD and FLAGS environment variables in the file
/etc/sysconfig/bitcoin_silverd. You can also use the DAEMONOPTS environment variable here.

### macOS

Copy org.bitcoin_silver.bitcoin_silverd.plist into ~/Library/LaunchAgents. Load the launch agent by
running `launchctl load ~/Library/LaunchAgents/org.bitcoin_silver.bitcoin_silverd.plist`.

This Launch Agent will cause bitcoin_silverd to start whenever the user logs in.

NOTE: This approach is intended for those wanting to run bitcoin_silverd as the current user.
You will need to modify org.bitcoin_silver.bitcoin_silverd.plist if you intend to use it as a
Launch Daemon with a dedicated bitcoin_silver user.

Auto-respawn
-----------------------------------

Auto respawning is currently only configured for Upstart and systemd.
Reasonable defaults have been chosen but YMMV.
