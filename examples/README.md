# Examples

*candump_reader* is used to extract wind data from the nmea
stream and format it into a rrdtool update statement. The
way I use it is as follows:

  rrdcreate -s 1 foo.rrd DS:speed:GAUGE:60:0:100 DS:dir:GAUGE:60:0:360 RRA:AVERAGE:0.5:1:864000
  candump can0 | ./candump_reader | rrdtool - >/dev/null &

You can then generate some amazing graphs, like this:

  /usr/bin/rrdtool graph - \
  --imgformat=PNG \
  --pango-markup  \
  --slope-mode \
  --base=1000 \
  --height=150 \
  --width=500 \
  --alt-autoscale-max \
  --lower-limit='0' \
  --color BACK#F3F3F3 \
  --color CANVAS#FDFDFD \
  --color SHADEA#CBCBCB \
  --color SHADEB#999999 \
  --color FONT#000000 \
  --color AXIS#2C4D43 \
  --color ARROW#2C4D43 \
  --color FRAME#2C4D43 \
  --border 1 --font TITLE:11:'Arial' \
  --font AXIS:8:'Arial' \
  --font LEGEND:8:'Courier' \
  --font UNIT:8:'Arial' \
  --font WATERMARK:6:'Arial' \
  --slope-mode \
  DEF:a='/var/lib/cacti/rra/foo.rrd':'speed':MAX \
  DEF:b='/var/lib/cacti/rra/foo.rrd':'dir':MAX \
  CDEF:cdefe='b,10,/' \
  LINE1:a#0000FFFF:  \
  GPRINT:a:LAST:'Cur\:%8.2lf %s'  \
  GPRINT:a:AVERAGE:'Avg\:%8.2lf %s'  \
  GPRINT:a:MAX:'Max\:%8.2lf %s\n'  \
  LINE1:cdefe#C04000FF:  \
  GPRINT:b:LAST:'Cur\:%8.2lf %s'  \
  GPRINT:b:AVERAGE:'Avg\:%8.2lf %s'  \
  GPRINT:b:MAX:'Max\:%8.2lf %s\n' > README.png

![Example graph](README.png?raw=true "Example")
