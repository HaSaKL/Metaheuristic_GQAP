# Read the data from csv-file produced by the C++-Program
data <- read.csv2(file = "ResultsLS+PR-Tests.csv", dec = ".", strip.white = T,  header=TRUE, fill = F,
          colClasses = c('factor', 'factor', 'factor','factor','factor','factor','numeric','numeric','numeric','numeric','numeric') );

# label data accoring to code book
data$StartSol <- factor(data$StartSol, 
                        levels = c(0,1,2,3,4),
                        labels = c("Random Init", "Greedy Init", "GRASP Init (Fixed Alpha)", "GRASP Init (Reactive Alpha)", "GRASP Init (Random Alpha)"))

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
                  mean_Time = mean(Time), 
                  mean_Iterations = mean(Iterations),
                  mean_Iter_Time = mean(iter_Time),
                  median_Time = median(Time),
                  median_Iterations = median(Iterations)
)

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
  xlim(0,5000) + geom_hline(1) +
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

png("PoolParameters_vs_Runtime.png",
    width = 16,
    height = 18,
    units = "cm",
    res = 1200,
    pointsize = 12,
    antialias = "cleartype"
)

ggplot(data = smry, aes(x=PRDir, y=PRPoolSelect, fill=median_Time)) +
  geom_tile() +
  facet_grid(PRMeth ~ StartSol) +
  theme_bw(base_size = 12, base_family = "serif") +
  theme (legend.position = "bottom",
         legend.direction = "horizontal",
         legend.background = element_rect(colour = "black"),
         panel.grid.major = element_blank()
  ) +
  scale_fill_gradient(low="gray10", 
                      high="gray90", 
                      name = "Median Runtime in seconds", 
                      guide=guide_colorbar(title.vjust = 0.7,
                                           title.position = "top",
                                           barwidth = 9
                      )
  ) +
  xlab("Path-Relinking Direction") + 
  ylab("Solution Pool Selector")
  

dev.off()

