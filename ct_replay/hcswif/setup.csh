#!/usr/bin/csh

# -----------------------------------------------------------------------------
#  Change these if this if not where hallc_replay and hcana live
#setenv hcana_dir "/home/$USER/hcana"
setenv hcana_dir "/w/hallc-scifs17exp/e1206107/CT12GeV/hcana"
#setenv hallc_replay_dir "/home/$USER/hallc_replay"
setenv hallc_replay_dir "/w/hallc-scifs17exp/e1206107/CT12GeV/ct_replay"

# -----------------------------------------------------------------------------
#  Change if this gives you the wrong version of root, evio, etc
source /site/12gev_phys/softenv.csh 2.1

# -----------------------------------------------------------------------------
# Source setup scripts
set curdir=`pwd`
cd $hcana_dir
source setup.csh
setenv PATH "$hcana_dir/bin:$PATH"
echo Sourced $hcana_dir/setup.csh

cd $hallc_replay_dir
source setup.csh
echo Sourced $hallc_replay_dir/setup.csh

echo cd back to $curdir
cd $curdir

