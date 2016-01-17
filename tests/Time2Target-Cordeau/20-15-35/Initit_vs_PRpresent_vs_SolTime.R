# Read the data from csv-file produced by the C++-Program
woPR_data <- read.csv2(file = "Test-20-15-35-woPR.csv", dec = ".", strip.white = T,  header=TRUE, fill = F,
                  colClasses = c('factor', 'factor', 'factor','factor','factor','factor','numeric','numeric','numeric','numeric','numeric') )

PR_data <- read.csv2(file = "ResultsLS+PR-Tests.csv", dec = ".", strip.white = T,  header=TRUE, fill = F,
                     colClasses = c('factor', 'factor', 'factor','factor','factor','factor','numeric','numeric','numeric','numeric','numeric') )

data <- rbind(woPR_data, PR_data)

# label data accoring to code book
data$StartSol <- factor(data$StartSol, 
                        levels = c(0,1,2,3,4),
                        labels = c("Random init", "Greedy init", "Fixed alpha", "Reactive alpha", "Uniform random alpha"))

data$LSStrategy <- factor(data$LSStrategy,
                          levels = c(0,1,2),
                          labels = c("best improve", "random improve", "none"))

data$PRMeth <- factor(data$PRMeth,
                      levels = c(0,1,2,3),
                      labels = c("Random PR-Move Selector", "Greedy PR-Move Selector", "GRASP PR-Move Selector", "no PR"))

data$PRDir <- factor(data$PRDir,
                     levels = c(0,1,2),
                     labels = c("Forward", "Backward", "Mixed"))

data$PRPoolSelect <- factor(data$PRPoolSelect,
                            levels = c(0,1,2),
                            labels = c("Diverse", "Random", "All"))

## get nice summary table
# use dplyr-Packe for easier handling
library(dplyr)

# filter relevant experiments
plotdata_wo_PR_Random <- filter(data, StartSol == "Random init", PRMeth == "no PR", LSStrategy == "random improve")
plotdata_wo_PR_Random <- mutate(plotdata_wo_PR_Random, Algo = 1)

plotdata_wo_PR_Reactive <- filter(data, StartSol == "Reactive alpha", PRMeth == "no PR", LSStrategy == "random improve")
plotdata_wo_PR_Reactive <- mutate(plotdata_wo_PR_Reactive, Algo = 2)

plotdata_with_PR_Random <- filter(data, StartSol == "Random init", PRMeth == "Greedy PR-Move Selector", 
                                  LSStrategy == "random improve", PRDir == "Backward", PRPoolSelect == "Random")
plotdata_with_PR_Random <- mutate(plotdata_with_PR_Random, Algo = 3)

plotdata_with_PR_Reactive <- filter(data, StartSol == "Reactive alpha", PRMeth == "Greedy PR-Move Selector", 
                                    LSStrategy == "random improve", PRDir == "Forward", PRPoolSelect == "All")
plotdata_with_PR_Reactive <- mutate(plotdata_with_PR_Reactive, Algo = 4)

# combine them to on dataframe and label data frame
plotdata <- rbind(plotdata_with_PR_Reactive, plotdata_with_PR_Random, plotdata_wo_PR_Random, plotdata_wo_PR_Reactive)
plotdata$Algo <- factor(plotdata$Algo, 
                        levels = c(1,2,3,4),
                        labels = c("Random init, w/o PR", "GRASP init, w/o PR", "Random init and PR", "GRASP init and PR"))

# group data by Neighborhood, Algorithm and Alphavalue
plotdata <- group_by(plotdata, StartSol, LSStrategy, PRMeth, PRDir, PRPoolSelect, Algo)

plotdata <- mutate(plotdata, Time = Time / 1000)
plotdata <- arrange(plotdata, PRMeth, StartSol)

library(ggplot2)

png("Init_vs_Time_Violin_woPR.png",
    width = 12,
    height = 5.5,
    units = "cm",
    res = 1200,
    pointsize = 10,
    antialias = "cleartype"
)

ggplot(data = plotdata, aes(x=Algo, y=Time)) +
  geom_violin() +
  geom_boxplot(width=0.1) +
  coord_flip() + 
  theme_bw(base_size = 10, base_family = "serif") +
  theme (legend.position = "bottom",
         legend.direction = "horizontal",
         legend.background = element_rect(colour = "black"),
         panel.grid.major = element_blank(),
         panel.grid.minor = element_blank(),
         axis.title.y = element_blank()
  ) +
  labs(y = "Runtime in sec")
  

dev.off()



