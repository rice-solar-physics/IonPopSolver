#quick_plot.py
#Author: Will Barnes
#Date:11 March 2016
#Description: Provide simple results plot from IonPopSolver code

#Import needed modules
import sys
import numpy as np
import seaborn.apionly as sns
import matplotlib.pyplot as plt
import argparse
import roman
import periodictable

#command line argument parsing
parser = argparse.ArgumentParser(description='Plot results from IonPopSolver.')
parser.add_argument("-Z","--element",type=int,help="Atomic number of element")
parser.add_argument("-f","--spec_from",type=int,help="Starting ion")
parser.add_argument("-t","--spec_to",type=int,help="Ending ion")
parser.add_argument("-O","--output_file",help="Output file from IonPopSolver")
parser.add_argument("--print_fig_filename",help="Root directory to which figures will be output.")
args = parser.parse_args()

#import results
results=np.loadtxt(args.output_file)
#check dimensions
_,c = np.shape(results)
if c-4 != args.spec_to-args.spec_from+1:
    print("Mismatch between spectroscopic indices(%d) and results file(%d)."%(args.spec_to-args.spec_from+1,c-4))
    print("Exiting...")
    sys.exit()
    
num_ipf = c-4
spec_labs = []
[spec_labs.append(roman.toRoman(i)) for i in range(args.spec_from,args.spec_to+1)]
spec_colors = []
cpal = sns.color_palette('husl',num_ipf)
[spec_colors.append(cpal[i]) for i in range(num_ipf)]

#aesthetics
fs=18
fs_eps=0.65

#slice results
t=results[:,0]
T=results[:,1]
Teff=results[:,2]
n=results[:,3]
Yz=results[:,4:]

#setup figure
fig,axes = plt.subplots(3,1,figsize=(10,8),sharex=True)
#plt.subplots_adjust(hspace=0.0)
axes[0].plot(t,T/1e+6,linestyle='-',color=sns.color_palette('deep')[0],linewidth=2,label=r'$T$')
axes[0].plot(t,Teff/1e+6,linestyle='-',color=sns.color_palette('deep')[2],linewidth=2,label=r'$T_{eff}$')
axes[1].plot(t,n/1e+8,linestyle='-',color=sns.color_palette('deep')[0],linewidth=2)
for i in range(num_ipf):
    axes[2].plot(t, Yz[:,i], linestyle='-', color=spec_colors[i], label=r'$\mathrm{%s}$ $\mathrm{%s}$'%(str(periodictable.elements[args.element]),spec_labs[i]), linewidth=2)
    
#labels
axes[0].set_ylabel(r'$T$ $(\mathrm{MK})$',fontsize=fs)
axes[1].set_ylabel(r'$n$ $(10^8\,\mathrm{cm}^{-3})$',fontsize=fs)
axes[2].set_ylabel(r'$Y_i,\,Z=%d$'%(args.element),fontsize=fs)
axes[2].set_xlabel(r'$t\,(\mathrm{s})$',fontsize=fs)
#limits
axes[2].set_xlim([t[0],t[-1]])
#ticks
axes[0].tick_params(axis='y',pad=8,labelsize=fs_eps*fs)
axes[1].tick_params(axis='y',pad=8,labelsize=fs_eps*fs)
axes[2].tick_params(axis='y',pad=8,labelsize=fs_eps*fs)
#legends
axes[0].legend(loc='best',fontsize=fs_eps*fs)
axes[2].legend(loc=1,ncol=4,fontsize=0.55*fs)

plt.tight_layout()

#save or show
if args.print_fig_filename is not None:
    plt.savefig(args.print_fig_filename+'.png',format='png',dpi=500)
else:
    plt.show()
