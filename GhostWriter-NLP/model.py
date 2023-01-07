# -*- coding: utf-8 -*-
"""413 Project

Automatically generated by Colaboratory.

Original file is located at
    https://colab.research.google.com/drive/1Hu1xn5BhDN89rdEEP4fEtp7VpjaaTdtM
"""

!nvidia-smi



!cat /proc/meminfo

!pip3 install pronouncing
!pip3 install kaggle
!pip3 install markovify
!pip3 install textstat
!pip3 install better-profanity

"""Prep and Split data into Train_Set and Test_Set

"""

from torch.utils.data import Dataset
import pandas as pd

lyrics_data_Drake = open('/content/lyrics_data/Drake_lyrics.txt', mode='r', encoding='utf8').read().split('\n')
lyrics_data_Childish = open('/content/lyrics_data/Childish Gambino_lyrics.txt', mode='r', encoding='utf8').read().split('\n')
lyrics_data_Kanye = open('/content/lyrics_data/Kanye West_lyrics.txt', mode='r', encoding='utf8').read().split('\n')

raw_data_Drake = {'Drake_data': [line for line in lyrics_data]}
#raw_data_Childish = {'Childish_data': [line for line in lyrics_data]}
#raw_data_Kanye = {'Kanye_data': [line for line in lyrics_data]}

df = pd.DataFrame(raw_data, columns = ['Drake_data'])

#shuffle dataset... is this necessary?
shuffle_dataframe = df.sample(frac=1)

#define size of training dataset
train_size = int(0.5*len(df))

#split into training and test set
train_set = shuffle_dataframe[:train_size]
test_set = shuffle_dataframe[train_size:]

#output for torchtext (needs a tabular dataset)
train_set.to_json('train.json', orient = 'records', lines =True)
test_set.to_json('train.json', orient = 'records', lines =True)

train_set.to_csv('train.csv', index=False)
test_set.to_csv('train.csv', index=False)

print(train_set), print(test_set)

"""Markov model to generate beginning sequence of each bar."""

import markovify

#build Markov Model from training set
#markov_model = markovify.NewlineText(train_set)

markov_model_Drake = markovify.NewlineText(lyrics_data_Drake)
markov_model_Childish = markovify.NewlineText(lyrics_data_Childish)
markov_model_Kanye = markovify.NewlineText(lyrics_data_Kanye)

#generate 4 random sentences
"""
print("Test Run Drake\n")
for i in range(4):
  print(markov_model_Drake.make_sentence())

print("\n")
print("Test Run Chidish Gambino\n")
for i in range(4):
  print(markov_model_Childish.make_sentence())

print("\n")
print("Test Run Kanye\n")
for i in range(4):
  print(markov_model_Kanye.make_sentence())

print("\n")

"""

#generate some short random sentences of  x_chars or less
x_chars = 50
print("Drake\n")
for i in range(4):
  print(markov_model_Drake.make_short_sentence(x_chars))
print("\n")

"""
print("Childish Gambino\n")
for i in range(4):
  print(markov_model_Childish.make_short_sentence(x_chars))
print("\n")

print("Kanye\n")
for i in range(4):
  print(markov_model_Kanye.make_short_sentence(x_chars))
print("\n")
"""

"""SimpleRNN
 - will take the markov generated sequence (bar) and add one last word to it
"""

import torchtext
import torch
import torch.nn as nn
import torch.optim as optim
import torch.nn.functional as f
from torch.utils.data import DataLoader
from torchtext.data.utils import get_tokenizer
from torchtext.legacy.data import Field, TabularDataset, BucketIterator

#Tokenizizer
def tokenizer(input):
  return [tok.text for tok in tokenizer(text)]

#Create Dictionary
fields = {'label':()}

#pad to get same size sequence
#feed seq to model


#create x and y data for training -- already have train set and test set
train_data, test_data = TabularDataset.splits(
    path = '', 
    train = 'train.json',
    test = 'test.json',
    format = 'json',
    fields = fields
)


#train_x == full bar minus last word


#train_y == last word

#RNN Model
class RNN(nn.Module):
  def __init__(self, input_size, hidden_size, output_size): #input size is vector*vector (....)
    super(RNN, self).__init__()
    self.i2h = nn.Linear(input_size + hidden_size, hideen_size)
    self.i2o = nn.Linear(input_size + hidden_size, output_size)
    self.softmax = nn.LogSoftmax(dim=1)
    

  def forward (self, input_tensor, ):
    x = f.relu(self.fc1(x))
    x = self.fc2(x)
    return x
"""  
model = NN(100, 10)
#figure out what size we want to return
x = torch.randn(10, 20)
print(model(x).shape)
"""

#run on device (GPU or CPU)
device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')


#hyperparameters (input size of vector, sequence, num layers, hidden layers, hidden size)
input_size = 512
num_classes = 10
learning_rate = 0.001
batch_size = 10
num_epochs = 50

#load data for training
#check if train_data is in correct format
train_loader = DataLoader(dataset=train_set, batch_size=batch_size, shuffle = True)
test_loader = DataLoader(dataset=test_set, batch_size=batch_size, shuffle = True)

#do we need to initialize network? cpu/cuda?

#optimizer and loss function
criterion = nn.CrossEntropyLoss()
optimizer = optim.Adam(model.parameters(), lr = learning_rate)

#Training Step
for epoch in range(num_epochs, category_tensor):
  for batch_index ,(data, targets) in enumerate(train_loader):
    data = data.to(device device)
    targets = targets.to(device=device)

    data = data.shape[1]
    #we have one dimension (one column in data), but we have a dictionary inside each colm.
    
    #forward part of NN
    scores = mode(data)
    #loss = criterion(scores, targets)
    loss = criterion(output, category_tensor)

    #backward, we don't go bckwd so we set gradient to 0 for every batch, so we don't store back props
    optimizer.zero_grad()
    loss.backward()

    #gradient descent, update weights based on loss.backward
    optimizer.step()

    return otput, loss.item()

#training loop
current_loss = 0
all_losses = []
plot_steps, print_steps = 1000, 5000
num_iter = 100000
for i in range(num_iter):
# ...

#Metric for testing
def score_bar():


#rhyme density
def calc_rhyme_density(bars):