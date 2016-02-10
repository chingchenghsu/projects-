
# coding: utf-8

##  Time series modeling: SP500 index Modeling <br>  

#### Author: Ching-Cheng Hsu   </font> <br> email: chingchenghsu.physics@googlemail.com 

# Prerequisite: <br>
# 1. We need python statsmodel package for time series statistical analysis. It can be installed from <a href="http://statsmodels.sourceforge.net/"> here</a> .   
# 
# Note: <br>
# 1. The statsmodel in Python is still not full developed. The models like ARCH and GARCH, which are commonly used in financial time series analysis is not there, from my understanding. Thus, I am suggesting to use R language to do such kind of analysis instead of Python. There are more libraries supported in R.  

# In[649]:

import csv
import numpy as np
import urllib2
from matplotlib import pyplot
from numpy import genfromtxt
from pandas.stats.moments import ewma
import statsmodels as sm
import statsmodels.api as smapi


# In[650]:

url = 'https://raw.githubusercontent.com/pymc-devs/pymc3/master/pymc3/examples/data/SP500.csv'


# In[651]:

my_data =  np.genfromtxt(url)


# <b> We plot all of indeces and get a feeling how it evolves with time  </b>

# In[652]:

plot(my_data,'k', label="original indices")
legend(loc='upper right')


# In principle, I can use part of the data (say 90%) for fitting the model and the rest (10%) for evaluation of the model by its prediction ability. But in this particular case, it is probably not going to work out properly.  <br>
# The plot shows that the indices don't have obvious "trend" or "seasonal" effect. However, there are periods which show stochastic behaviors (means state which changes in a random way.).  

#  We first investigate if this process is one of the classic examples of stochastic process: Random Walk   <br>
#  Random walk has a feature:  $$X_{t}  =  X_{t-1} + w_{i} $$     where $w_{i}$ are noise terms. If it is random walk process, the  $w_{i}$ will show  discrete white noise (DWN) behavior.  It can be seen from the ACF (auto-correlation function) plot.  

# So we start to apply the auto-correlation function

# In[653]:

ylim([-0.1,0.1])
xlim([0,3800])
my_data_acf=sm.tsa.stattools.acf(diff(my_data), nlags=3820)
''' Apply ACF function on the first order differencing of each terms'''
plot(my_data_acf, 'b', label="ACF plot of the difference between neighboring terms")
axhline(y=0.05, xmin=0., xmax=100, linewidth=2, color = 'r')
axhline(y=-0.05, xmin=0., xmax=100, linewidth=2, color = 'r')
legend(loc='upper right')


# <font size="3"> Zoom in the plot in X-direction (Only shows the lag from 0 to 50) </font>

# In[654]:

ylim([-0.1,0.1])
xlim([0,50])
plot(my_data_acf, 'b', label="ACF plot of the difference between neighboring terms")
axhline(y=0.05, xmin=0., xmax=100, linewidth=2, color = 'r')
axhline(y=-0.05, xmin=0., xmax=100, linewidth=2, color = 'r')
legend(loc='upper right')


# The 5% line is a criteria for strength of the correlation. If the ACF coef. is larger than 5%, means at that particular lag, there is a strong correlation between two series (which we don't want for the DWN.).  We can read detail theories from  <a href="http://sfb649.wiwi.hu-berlin.de/fedc_homepage/xplore/tutorials/xegbohtmlnode39.html"> here </a> 

# In[655]:

index=0
print "lags,    coef. "
for xx in my_data_acf:
    if abs(xx) >0.05:
        print index,"  ", xx
    index=index+1 


# <font size="3"> We start to investigate how many terms in the ACF function coefficients have larger than 0.05. 
# From above, we know that at lag k=1,11,16,18.... etc, the ACF coef. are larger than 5%. <br> </font>

# This means the SP500 index is not pure "random walk" process. Because the difference between two nearby numbers are not pure white noise (Thay have correlations).  Thus we need to model it with more complicated models.   <br>
# Let's try more general model which is ARMA model. ARMA model is a combination of AR and MA model. The details of ARMA model could be seen from <a href="https://en.wikipedia.org/wiki/Autoregressive%E2%80%93moving-average_model" > here </a> 
# 
# In priciple, we can "guess" what order (p,q) of ARMA model is the best fit of our data based on ACF and PACF function. However, it is very tricky, see <a href="http://sfb649.wiwi.hu-berlin.de/fedc_homepage/xplore/tutorials/xegbohtmlnode39.html"> here </a> for detail discussions. Here I choose the model based on the Bayesian information criterion (BIC) information.   

# In[656]:

final_bic =100000.
current_bic=0.
final_pq=[0,0]
for p in range(0,4):
    for q in range(0,2):
        arma_mod = smapi.tsa.ARMA(diff(my_data), (p,q)).fit()
        current_bic = arma_mod.bic
        print(p, q, current_bic)
        print(smapi.stats.durbin_watson(arma_mod.resid))


# From above, I choose ARMA model with order (3,1). It has low BIC value and Durbin-Watson test on the residues. Normally people suggest to use models with smaller BIC values.  

# In[657]:

arma_mod = smapi.tsa.ARMA(diff(my_data), (3,1)).fit()
print(arma_mod.params)


# In[658]:

arma_mod.summary()


# In[659]:

fitresult = []
''' fitresult is a list which contains the fitted information '''
for ii in range(0,arma_mod.k_ar-1):
    fitresult.append(0)
    ''' Note this is because fitresult array will have only len(my_data) elements.
        In order not to have time offset with respect to the my_data array, 
        we have to put arma_mod.kar-1 0s in the beginning of the array ''' 
for t in range(arma_mod.k_ar, len(my_data)+1):
    value = arma_mod.params[0]
    for i in range(2, arma_mod.k_ar + 2):
        value += arma_mod.params[i - 1] * my_data[t - i + 1]
    fitresult.append(value)


# In[660]:

plot(my_data,'r', label="Original Data")
plot(fitresult,'b', label="ARMA(3,1) Model")
legend(loc='upper right')


# In[661]:

ylim([-0.1,0.1])
xlim([0,3900])
plot(sm.tsa.stattools.acf(arma_mod.resid ,nlags=3900), 'b', label="acf plot of Residues of ARMA model and Data")
axhline(y=0.05, xmin=0., xmax=100, linewidth=2, color = 'r')
axhline(y=-0.05, xmin=0., xmax=100, linewidth=2, color = 'r')


# In[662]:

index=0
for xx in sm.tsa.stattools.acf(arma_mod.resid ,nlags=3813):
    if abs(xx) >0.05:
        print index, xx
    index+=1


# It is obvious that the ACF is better in ARMA model than in Random Walk model. The ACF shows only one term with larger than 0.05. 

# In[663]:

sm.stats.diagnostic.acorr_ljungbox(sm.tsa.stattools.acf(arma_mod.resid),lags=20)


# We start using the <a href="https://en.wikipedia.org/wiki/Ljung%E2%80%93Box_test" > Ljung–Box test </a>. It is a test for whether any of a group of autocorrelations of a time series are different from zero. It is reported Ljung-Box test has better small sample properties compared to another test which is Box-Pierce statistic.
# The probaility p-value (the second array) are all larger than 5%. Means this model is sort of good. 

# In[664]:

size=3900
sample=10
predict_data=np.zeros(size)
predict_data[0:len(my_data)] = np.asarray(fitresult[0:len(my_data)]).copy()
from statsmodels.tsa.arima_model import _arma_predict_out_of_sample
predict_data[len(my_data):len(my_data)+sample]= _arma_predict_out_of_sample(arma_mod.params, sample, arma_mod.resid, 3, 1, arma_mod.k_trend, arma_mod.k_exog, endog=my_data, exog=None, start=len(my_data))*sample


# Here, we start to predict the future values based on our fitted model. 

# In[665]:

xlim(3750,3850)
ylim(-0.03,0.03)
plot(my_data,'r',linewidth=2, label="Original Data")
plot(fitresult,'b', linewidth=2, label="ARMA(3,1) Model Fitted")
plot(predict_data[0:len(my_data)+sample], 'g',linewidth=2, linestyle='--', label="Predict Values")
legend(loc='upper right')


# The prediction is done with 10 steps further. <br> 
# <br>

# <b> The Conclusion: </b>  <br>   
# 1. Normally, in order to tackle the financial time series problem, we have to use Autoregressive Conditional Heteroscedasticity (ARCH) model or Generalised Autoregressive Conditional (GARCH) model. These models deal with time variant  volatilities. The term "Heteroscedasticity" means if there are certain groups, or subsets, of variables within the larger set of data that have a different variance from the remaining variables.
#     This is usually the case in finance. <br>
# 2. Unfortunately, so far, I could not find proper python supported libraries about ARCH or GARCH model. I am going to use rpy2 (calling R inside Python) to repeat the analysis.  
