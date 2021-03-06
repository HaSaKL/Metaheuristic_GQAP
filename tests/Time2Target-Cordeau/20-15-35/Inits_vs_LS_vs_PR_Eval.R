# Read the data from csv-file produced by the C++-Program - without quick GRASP
dataNotQuick <- read.csv2(file = "ResultsLS+PR-Tests.csv", dec = ".", strip.white = T,  header=TRUE, fill = F,
          colClasses = c('factor', 'factor', 'factor','factor','factor','factor','numeric','numeric','numeric','numeric','numeric') );

dataNotQuick <- subset(dataNotQuick, select = -X)

# Additionally read the data with quick GRASP and alter the Initialization Method accordingly
# also drop the PoolSize, since it was not considered in the first test runs
dataQuick <- read.csv2(file = "ResultsLS+PR-Tests-quick.csv", dec = ".", strip.white = T,  header=TRUE, fill = F,
          colClasses = c('factor', 'factor', 'factor','factor','factor','factor','numeric','numeric','numeric','numeric','numeric') );

dataQuick <- subset(dataQuick, select = -PoolSize)

levels(dataQuick$StartSol)[levels(dataQuick$StartSol) == 3] <- 7
levels(dataQuick$StartSol)[levels(dataQuick$StartSol) == 4] <- 8


# merge quick and not quick data

data <- rbind(dataQuick, dataNotQuick)

 
# label data accoring to code book

data$StartSol <- factor(data$StartSol, 
                                levels = c(0,1,2,3,4,5,6,7,8),
                                labels = c("Random init", 
                                           "Greedy init", "Fixed alpha", "Reactive alpha", "Uniform random alpha",
                                           "Quick Greedy", "Quick Fixed", "Quick Reactive", "Quick Uniform Random"))

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

# group data by Neighborhood, Algorithm and Alphavalue
gr_data <- group_by(data, StartSol, LSStrategy, PRMeth, PRDir, PRPoolSelect)

# order data Neighborhood, Algorithm and Alphavalue
gr_data <- arrange(gr_data, StartSol, LSStrategy, PRMeth, PRDir, PRPoolSelect)


# calculate time per iteration
gr_data <- mutate(gr_data, iter_Time = Time / Iterations)

# summarize data by calculating mean and median values for each module size for viewing pleasure
smry <- summarise(gr_data, 
                  min_Time = min(Time),
                  max_Time = max(Time),
                  mean_Time = mean(Time), 
                  mean_Iterations = mean(Iterations),
                  mean_Iter_Time = mean(iter_Time),
                  median_Time = median(Time),
                  median_Iterations = median(Iterations)
)

# deselect uniform random alpha
gr_data <- filter(gr_data, StartSol == "Random init" | StartSol == "Reactive alpha" | StartSol == "Quick Reactive")


## exploratroy drawing of Time-To-Target Plots to find out good parameter combinations
library(ggplot2)
gr_data_f <- filter(gr_data, LSStrategy == "random improve",PRPoolSelect == "Random")
png("Runtime_StartSol_vs_PRMeth_vs_PRDir_PoolSelectRandom.png",
    width = 20,
    height = 20,
    units = "cm",
    res = 1200,
    pointsize = 10,
    antialias = "cleartype"
)
ggplot(gr_data_f, aes(Time + 0.1, color = PRMeth, linetype = PRMeth)) + 
  stat_ecdf(geom='line') + 
  xlim(0,20000) + #geom_hline(y=1) +
  facet_grid(PRDir ~ StartSol, labeller = label_both) +
  ylab("ECDF") +
  xlab("Run Time")
dev.off()


gr_data_f <- filter(gr_data, LSStrategy == "random improve",PRPoolSelect == "Diverse")
png("Runtime_StartSol_vs_PRMeth_vs_PRDir_PoolSelectDiverse.png",
    width = 20,
    height = 20,
    units = "cm",
    res = 1200,
    pointsize = 10,
    antialias = "cleartype"
)
ggplot(gr_data_f, aes(Time + 0.1, color = PRMeth, linetype = PRMeth)) + 
  stat_ecdf(geom='line') + 
  xlim(0,20000) + #geom_hline(y=1) +
  facet_grid(PRDir ~ StartSol, labeller = label_both) +
  ylab("ECDF") +
  xlab("Run Time")
dev.off()


gr_data_f <- filter(gr_data, LSStrategy == "random improve",PRPoolSelect == "All")
png("Runtime_StartSol_vs_PRMeth_vs_PRDir_PoolSelectAll.png",
    width = 20,
    height = 20,
    units = "cm",
    res = 1200,
    pointsize = 10,
    antialias = "cleartype"
)
ggplot(gr_data_f, aes(Time + 0.1, color = PRMeth, linetype = PRMeth)) + 
  stat_ecdf(geom='line') + 
  xlim(0,20000) + #geom_hline(y=1) +
  facet_grid(PRDir ~ StartSol, labeller = label_both) +
  ylab("ECDF") +
  xlab("Run Time")
dev.off()


#############################


gr_data_f <- filter(gr_data, LSStrategy == "random improve",PRPoolSelect == "Random")
png("Iterations_StartSol_vs_PRMeth_vs_PRDir_PoolSelectRandom.png",
    width = 20,
    height = 20,
    units = "cm",
    res = 1200,
    pointsize = 10,
    antialias = "cleartype"
)
ggplot(gr_data_f, aes(Iterations, color = PRMeth, linetype = PRMeth)) + 
  stat_ecdf(geom='line') + 
  xlim(0,5000) + #geom_hline(y=1) +
  facet_grid(PRDir ~ StartSol, labeller = label_both) +
  ylab("ECDF") +
  xlab("Iterations")
dev.off()


gr_data_f <- filter(gr_data, LSStrategy == "random improve",PRPoolSelect == "Diverse")
png("Iterations_StartSol_vs_PRMeth_vs_PRDir_PoolSelectDiverse.png",
    width = 20,
    height = 20,
    units = "cm",
    res = 1200,
    pointsize = 10,
    antialias = "cleartype"
)
ggplot(gr_data_f, aes(Iterations, color = PRMeth, linetype = PRMeth)) + 
  stat_ecdf(geom='line') + 
  xlim(0,5000) + #geom_hline(y=1) +
  facet_grid(PRDir ~ StartSol, labeller = label_both) +
  ylab("ECDF") +
  xlab("Iterations")
dev.off()


gr_data_f <- filter(gr_data, LSStrategy == "random improve",PRPoolSelect == "All")
png("Iterations_StartSol_vs_PRMeth_vs_PRDir_PoolSelectAll.png",
    width = 20,
    height = 20,
    units = "cm",
    res = 1200,
    pointsize = 10,
    antialias = "cleartype"
)
ggplot(gr_data_f, aes(Iterations, color = PRMeth, linetype = PRMeth)) + 
  stat_ecdf(geom='line') + 
  xlim(0,5000) + #geom_hline(y=1) +
  facet_grid(PRDir ~ StartSol, labeller = label_both) +
  ylab("ECDF") +
  xlab("Iterations")
dev.off()



## Heatmap for Parameter Comparision

smry <- mutate(smry, median_Time = median_Time / 1000, mean_Time = mean_Time / 1000)
smry <- filter(smry, StartSol == "Random init" | StartSol == "Reactive alpha" | StartSol == "Quick Reactive")
smry <- filter(smry, LSStrategy == "random improve")

png("PoolParameters_vs_Runtime.png",
    width = 20,
    height = 15,
    units = "cm",
    res = 1200,
    pointsize = 14,
    antialias = "cleartype"
)

ggplot(data = smry, aes(x=PRDir, y=PRPoolSelect, fill=median_Time)) +
  geom_tile() +
  facet_grid(StartSol ~  PRMeth) +
  theme_bw(base_size = 14, base_family = "serif") +
  theme (legend.position = "bottom",
         legend.direction = "horizontal",
         legend.background = element_rect(colour = "black"),
         panel.grid.major = element_blank()
  ) +
  scale_fill_gradient(low="#333393", 
                      high="#B9B9FF", 
                      name = "Median solution time in seconds", 
                      trans = "log",
                      breaks = c(0.75,1.5,3),
                      guide=guide_colorbar(title.vjust = 0.7,
                                           title.position = "top",
                                           barwidth = 11
                      )
  ) +
  xlab("Path-Relinking Direction") + 
  ylab("Solution Pool Selector")
  
dev.off()