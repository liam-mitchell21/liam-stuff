
echo "Starting roscore"

BASE=$(rospack find mecanum_master)/scripts
$BASE/term.sh roscore & 
sleep 15