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
        scale_y_continuous(name=disp_name, breaks=seq(ylimits[1], ylimits[2], (ylimits[2]-ylimits[1])/3))

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


outputfilename <- "profile.pdf"
rawdata <- read.csv("../data/energy_profile3.csv", header=TRUE)
dfactor <- 15

columns <- c("Time","Current")

plotdata <- ''

for (column in columns) {
  print(column)
  column_values <- filter_and_decimate(rawdata[,column],dfactor)
  if (plotdata != '') {
    plotdata[column] <- column_values*50.0
  } else {
    plotdata <- data.frame(column_values-10)
  }
}

#plotdata["CurrentuA"] = plotdata[["Current"]] * 50.0

colnames(plotdata) <- columns


#sol1 <- plot_trace("Solar1",plotdata,"Time",FALSE, c(5.3,5.7), "Solar1")
#sol2 <- plot_trace("Solar2",plotdata,"Time",FALSE, c(3.8,4.2), "Solar2")
#both <- plot_trace("Both",plotdata,"Time",FALSE, c(3.8,4.2), "Both")
#vcc <- plot_trace("Vcc",plotdata,"Time",FALSE, c(3.8,4.2), "Vcc")
cur <- plot_trace("Current",plotdata,"Time",TRUE, c(0,90), "Current (µA)")
#hl1 <- plot_trace("HL1",plotdata,"Time",FALSE, c(3.8,4.2), "HL1")
#hl2 <- plot_trace("HL2",plotdata,"Time",TRUE, c(3.8,4.2), "HL2")

#plots <- list(cur);



#g <- arrangeGrob(grobs=plots, ncol=1, heights=c(1,1,1,1,2,1,1.4))

ggsave(outputfilename, width=4, height=2.5, pointsize=18, device=cairo_pdf,cur);
