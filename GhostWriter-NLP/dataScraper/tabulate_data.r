#options(warn=-1)
#library(data.table)

file_list = list.files('../input/rap-lyrics', pattern='*.txt')
names = strsplit(file_list, '_lyrics.txt')
names = as.character(names)
print(names)

dt = data.table()
for (i in 1:length(file_list)) {
  single_txt = readLines(paste0('../input/rap-lyrics/', file_list[i]))
  rpr = data.table(rapper=names[i],text = single_txt)
  dt = rbind(dt, rpr)
}

dt[,rapper:=ifelse(rapper=='Tupac1' | rapper=='Tupac2','Tupac',rapper)]
fwrite(dt,'rap_all.csv')
