library(ggplot2)
library(grid)
library(gridExtra)
library(signal)

plot_trace <- function(column, data, row, axis_element, ylimits, disp_name) {

  print(c("Plotting ",column))
  g <- ggplot(data, aes_string(x=row, y=column))+
        geom_line(aes_string(x=row, y=column))+
        expand_limits(y = ylimits) +
        xlab("Time (s)")+
        scale_y_continuous(name=disp_name, breaks=seq(ylimits[1], ylimits[2], (ylimits[2]-ylimits[1])/1))

  if (!axis_element) {
      g <- g+ theme(axis.title.x =element_blank(),
                  axis.text.x  =element_blank(),
                  axis.ticks.x =element_blank())
  }
  return(g)
}

filter_and_decimate <- function(vector, dfactor) {
  filt_type <- "fir"
  filt_n <- 26
  offset <- vector[1]
  result = pmax(decimate(vector-offset,dfactor, n=filt_n, ftype=filt_type)+offset,0)
  return(result)
}


outputfilename <- "acrossAndLinger.pdf"
rawdata1 <- read.csv("../data/Test1_LabDoorway_Harsh.csv", header=TRUE)
rawdata2 <- read.csv("../data/walkingby_3ft.csv", header=TRUE)
dfactor <- 100

columns <- c("Time","C", "B")

plotdata1 <- ''
plotdata2 <- ''
time_start1 = min(rawdata1[["Time"]])
time_start2 = min(rawdata2[["Time"]])

for (column in columns) {
  print(column)
  column_values1 <- filter_and_decimate(rawdata1[,column],dfactor)
  column_values2 <- filter_and_decimate(rawdata2[,column],dfactor)
  if (plotdata1 != '') {
    plotdata1[column] <- column_values1
  } else {
    plotdata1 <- data.frame(column_values1-time_start1)
  }

  if (plotdata2 != '') {
    plotdata2[column] <- column_values2
  } else {
    plotdata2 <- data.frame(column_values2-time_start2)
  }
}


colnames(plotdata1) <- columns
colnames(plotdata2) <- columns


through_c <- plot_trace("C",plotdata1,"Time",FALSE, c(3.85,4), "Solar\nIn+Out (V)\n(Through)")
through_b <- plot_trace("B",plotdata1,"Time",FALSE, c(2.6,2.9), "Solar\nOut (V)\n(Through)")
across_c <- plot_trace("C",plotdata2,"Time",FALSE, c(3.85,4), "Solar\nIn+Out (V)\n(Across)")
across_b <- plot_trace("B",plotdata2,"Time",TRUE, c(2.4,2.6), "Solar\nOut (V)\n(Across)")


plots <- list(through_c, through_b, across_c, across_b);



g <- arrangeGrob(grobs=plots, ncol=1, heights=c(1,1,1,1.2))

ggsave(outputfilename, width=4, height=4, pointsize=18, device=cairo_pdf,g);
