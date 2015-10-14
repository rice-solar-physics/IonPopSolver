#em_binner.py
#Will Barnes
#14 October 2015

#Class to construct emission measure (EM) distributions from temperature and density profiles. Incorporate effective temperature profiles due to non-equilibrium ionization.

#Import needed modules
import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt


class EM_Binner(object):
    
    def __init__(self,filename,loop_length,read_abundances=False,**kwargs):
        #Read File
        data = np.loadtxt(filename)
        #set loop length as member variable
        self.loop_length = loop_length
        #Slice array and set member arrays
        self.time = data[:,0]
        self.temp = data[:,1]
        self.temp_eff = data[:,2]
        self.density = data[:,3]
        #Get abundances
        if(read_abundances):
            print("TODO: import abundances")
            pass
            
    def logT_bins(self,logT_a=4.0,logT_b=8.5,delta_logT=0.01):
        """Build temperature bins in log_10 for creating EM distribution"""
        
        self.logT_EM = np.arange(logT_a,logT_b,delta_logT)
        
    def emission_measure_calc(self,n):
        """Calculate emission measure distribution"""
        
        return self.loop_length*n**2
        
    def coronal_limits(self,T):
        """Find limits of corona in log temperature space."""
        
        #Use EBTEL method for calculating coronal temperature bounds
        logT_C_a = np.log10(2.0/3.0*T)
        logT_C_b = np.log10(10.0/9.0*T)
        return logT_C_a,logT_C_b
        
    def build_em_dist(self):
        """Create EM distribution from temperature arrays. Build for both T and T_eff"""
        
        try:
            self.logT_bins
        except NameError:
            print("Temperature bins not yet created. Building now with default values.")
            self.logT_bins()
            
        #Multidimensional EM object
        em_mat = np.zeros((len(self.time),len(self.logT_bins)))
        em_eff_mat = np.zeros((len(self.time),len(self.logT_bins)))
            
        #Loop over time
        for i in range(len(self.time)):
            #calculate coronal temperature bounds at time i
            logTa,logTb = self.coronal_limits(self.temp[i])
            logTa_eff,logTb_eff = self.coronal_limits(self.temp_eff[i])
            #find coronal indices in logT
            iC = np.where((self.logT_EM >= logTa) & (self.logT_EM <= logTb))
            iC_eff = np.where((self.logT_EM >= logTa_eff) & (self.logT_EM <= logTb_eff))
            #set EM at time i to EM in entries corresponding to the corona
            em_mat[i,iC[0]] = self.emission_measure_calc(self.density[i])
            em_eff_mat[i,iC_eff[0]] = self.emission_measure_calc(self.density[i])
            
        #Compute weighted averages over all time and take log
        self.em = np.log10(np.average(em_mat,axis=0,weights=np.gradient(self.time)))
        self.em_eff = np.log10(np.average(em_eff_mat,axis=0,weights=np.gradient(self.time)))
            
            
            