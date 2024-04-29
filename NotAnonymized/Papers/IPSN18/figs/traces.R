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


outputfilename <- "tracesout.pdf"
rawdata <- read.csv("../data/trace_out.csv", header=TRUE)
dfactor <- 20

columns <- c("Time","Solar.in","Solar.out","HL.in","HL.out")
columns_names <- c("Time (s)", "Solar volts (in)", "Solar volts (out) ","Detect(in)"," Detect(out)")

plotdata <- ''

for (column in columns) {
  print(column)
  column_values <- filter_and_decimate(rawdata[,column],dfactor)
  if (plotdata != '') {
    plotdata[column] <- column_values
  } else {
    plotdata <- data.frame(column_values)
  }
}

plotdata["D.in"] = pmax(plotdata[["HL.in"]],0)
plotdata["D.out"] = pmax(plotdata[["HL.out"]],0)

colnames(plotdata) <- columns

#plots <- lapply(columns[-c(1)], plot_trace, data = plotdata, row="Time",axis_element=tail(columns,1));

ps_in <- plot_trace("Solar.in",plotdata,"Time",FALSE, c(2.7,2.9), "Solar-In (V)")
ps_out <- plot_trace("Solar.out",plotdata,"Time",FALSE, c(2.7,2.9), "Solar-Out (V)")
d_in <- plot_trace("HL.in",plotdata,"Time",FALSE, c(0,2.1), "Detect-In")
d_out <- plot_trace("HL.out",plotdata,"Time",TRUE, c(0,2.1),"Detect-Out")

plots <- list(ps_in, ps_out, d_in, d_out);



g <- arrangeGrob(grobs=plots, ncol=1, heights=c(1,1,1,1.4))

ggsave(outputfilename, width=4, height=4, pointsize=18, device=cairo_pdf,g);
