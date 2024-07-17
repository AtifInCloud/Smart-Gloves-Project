
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns

from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import classification_report
import pandas as pd


df1 = pd.read_csv('okaydone.csv')

#print(df1.head())

df1 = df1[df1.columns[0:11]]


df1['sign'] = 'okay'

df2 = pd.read_csv('stopdone.csv')

df2 = df2[df2.columns[0:11]]

df2['sign'] = 'stop'

df3 = pd.read_csv('adone.csv')

df3 = df3[df3.columns[0:11]]

df3['sign'] = 'A'

df4 = pd.read_csv('bdone.csv')

df4  = df4[df4.columns[0:11]]

df4['sign'] = 'B'


df5 = pd.read_csv('helpdone.csv')

df5 = df5[df5.columns[0:11]]

df5['sign'] = 'help'

df  = pd.concat([df1,df2,df3,df4,df5])

#print(type(df))

#print(df)

print(df.head())
new_df = df.sample(frac=1)

new_df = new_df.fillna(new_df.mean())
df_X = new_df.drop(["sign"], axis=1)
df_Y = new_df["sign"]

X_train,X_test,y_train,y_test =train_test_split(df_X,df_Y,test_size=0.30)

rf = RandomForestClassifier(n_estimators=50,random_state=3,max_depth = 5)

rf.fit(X_train,y_train)

print(rf.score(X_test,y_test))

#print(new_df)

import pickle5 as pickle 

pickle.dump(rf, open('word_model1','wb'))


