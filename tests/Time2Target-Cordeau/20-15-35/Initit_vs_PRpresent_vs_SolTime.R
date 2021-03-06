# Read the data from csv-file produced by the C++-Program
woPR_data <- read.csv2(file = "Test-20-15-35-woPR.csv", dec = ".", strip.white = T,  header=TRUE, fill = F,
                  colClasses = c('factor', 'factor', 'factor','factor','factor','factor','numeric','numeric','numeric','numeric','numeric') )

PR_data <- read.csv2(file = "ResultsLS+PR-Tests.csv", dec = ".", strip.white = T,  header=TRUE, fill = F,
                     colClasses = c('factor', 'factor', 'factor','factor','factor','factor','numeric','numeric','numeric','numeric','numeric') )

data <- rbind(woPR_data, PR_data)

data <- subset(data, select = -X)


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


# read and transform quick GRASP data

quick_PR_data <- read.csv2(file = "ResultsLS+PR-Tests-quick.csv", dec = ".", strip.white = T,  header=TRUE, fill = F,
                     colClasses = c('factor', 'factor', 'factor','factor','factor','factor','numeric','numeric','numeric','numeric','numeric') )

quick_woPR_data <-  read.csv2(file = "Test-20-15-35-woPR-quick.csv", dec = ".", strip.white = T,  header=TRUE, fill = F,
                              colClasses = c('factor', 'factor', 'factor','factor','factor','factor','numeric','numeric','numeric','numeric','numeric') )

quick_data <- rbind(quick_PR_data, quick_woPR_data)

quick_data <- subset(quick_data, select = -PoolSize)

levels(quick_data$StartSol)[levels(quick_data$StartSol) == 3] <- 7
levels(quick_data$StartSol)[levels(quick_data$StartSol) == 4] <- 8

# label data accoring to code book
quick_data$StartSol <- factor(quick_data$StartSol, 
                        levels = c(0,1,2,3,4,5,6,7,8),
                        labels = c("Random init", 
                                   "Greedy init", "Fixed alpha", "Reactive alpha", "Uniform random alpha",
                                   "Quick Greedy", "Quick Fixed", "Quick Reactive", "Quick Uniform Random"))

quick_data$LSStrategy <- factor(quick_data$LSStrategy,
                          levels = c(0,1,2),
                          labels = c("best improve", "random improve", "none"))

quick_data$PRMeth <- factor(quick_data$PRMeth,
                      levels = c(0,1,2,3),
                      labels = c("Random PR-Move Selector", "Greedy PR-Move Selector", "GRASP PR-Move Selector", "no PR"))

quick_data$PRDir <- factor(quick_data$PRDir,
                     levels = c(0,1,2),
                     labels = c("Forward", "Backward", "Mixed"))

quick_data$PRPoolSelect <- factor(quick_data$PRPoolSelect,
                            levels = c(0,1,2),
                            labels = c("Diverse", "Random", "All"))

## get nice summary table
# use dplyr-Packe for easier handling
library(dplyr)

# filter relevant experiments

plotdata_with_PR_Random <- filter(data, StartSol == "Random init", PRMeth == "Greedy PR-Move Selector", 
                                  LSStrategy == "random improve", PRDir == "Forward", PRPoolSelect == "Random")
plotdata_with_PR_Random <- mutate(plotdata_with_PR_Random, Algo = 1)



plotdata_quick_with_PR_Reactive <- filter(quick_data, StartSol == "Quick Reactive", PRMeth == "Greedy PR-Move Selector", 
                                          LSStrategy == "random improve", PRDir == "Forward", PRPoolSelect == "All")
plotdata_quick_with_PR_Reactive <- mutate(plotdata_quick_with_PR_Reactive, Algo = 2)



plotdata_with_PR_Reactive <- filter(data, StartSol == "Reactive alpha", PRMeth == "Greedy PR-Move Selector", 
                                    LSStrategy == "random improve", PRDir == "Forward", PRPoolSelect == "All")
plotdata_with_PR_Reactive <- mutate(plotdata_with_PR_Reactive, Algo = 3)




plotdata_wo_PR_Random <- filter(data, StartSol == "Random init", PRMeth == "no PR", LSStrategy == "random improve")
plotdata_wo_PR_Random <- mutate(plotdata_wo_PR_Random, Algo = 4)


plotdata_quick_wo_PR_Reactive <- filter(quick_data, StartSol == "Quick Reactive", PRMeth == "no PR", LSStrategy == "random improve")
plotdata_quick_wo_PR_Reactive <- mutate(plotdata_quick_wo_PR_Reactive, Algo = 5)


plotdata_wo_PR_Reactive <- filter(data, StartSol == "Reactive alpha", PRMeth == "no PR", LSStrategy == "random improve")
plotdata_wo_PR_Reactive <- mutate(plotdata_wo_PR_Reactive, Algo = 6)







# combine them to on dataframe and label data frame
plotdata <- rbind(plotdata_with_PR_Reactive, 
                  plotdata_with_PR_Random, 
                  plotdata_wo_PR_Random, 
                  plotdata_wo_PR_Reactive, 
                  plotdata_quick_wo_PR_Reactive, 
                  plotdata_quick_with_PR_Reactive)
plotdata$Algo <- factor(plotdata$Algo, 
                        levels = c(1,2,3,4,5,6),
                        labels = c("Random Init\nwith PR",
                                   "Quick GRASP\nwith PR",
                                   "GRASP Init\nwith PR",
                                   "Random Init\nwithout PR",
                                   "Quick GRASP\nwithout PR",
                                   "GRASP Init\nwithout PR"))

# group data by Neighborhood, Algorithm and Alphavalue
plotdata <- group_by(plotdata, StartSol, LSStrategy, PRMeth, PRDir, PRPoolSelect, Algo)

plotdata <- mutate(plotdata, Time = Time / 1000)
plotdata <- arrange(plotdata, PRMeth, StartSol)

library(ggplot2)

  png("Init_vs_Time_Violin_woPR.png",
      width = 20,
      height = 12,
      units = "cm",
      res = 1200,
      pointsize = 14,
      antialias = "cleartype"
  )
  
  ggplot(data = plotdata, aes(x=Algo, y=Time)) +
    geom_violin() +
    #geom_boxplot(width=0.1, outlier.shape = NA) +
    geom_boxplot(width=0.1) +
    #scale_y_log10() +
    #coord_flip() + 
    theme_bw(base_size = 14, base_family = "serif") +
    theme (legend.position = "bottom",
           legend.direction = "horizontal",
           legend.background = element_rect(colour = "black"),
           panel.grid.major = element_blank(),
           panel.grid.minor = element_blank(),
           axis.title.x = element_blank()
    ) +
    labs(y = "Runtime in sec")
  
  
  dev.off()

