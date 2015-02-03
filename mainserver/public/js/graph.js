var graph = (function() {
    var obj = {};
    var selector;
    
    // Set the dimensions of the canvas / graph
    var margin = {top: 30, right: 20, bottom: 30, left: 50},
        width = 600 - margin.left - margin.right,
        height = 270 - margin.top - margin.bottom;

    // Parse the date / time
    var dateFormat = d3.time.format("%m/%d/%Y %H:%M:%S");

    // Set the ranges
    var x = d3.time.scale().range([0, width]);
    var y = d3.scale.linear().range([height, 0]);

    // Define the axes
    var xAxis = d3.svg.axis().scale(x)
        .orient("bottom").ticks(5);

    var yAxis = d3.svg.axis().scale(y)
        .orient("left").ticks(5);

    // Define the line
    var line = d3.svg.line()
        .x(function(d) { return x(d.date); })
        .y(function(d) { return y(d.measurement); });
        
    var tip = d3.tip()
            .attr('class', 'd3-tip')
            .offset([70, 40])
            .html(function(d) {
                return "<strong> pH: " + d.measurement + "</strong><br>"
                        + dateFormat(d.date) + "<br>";
    });
    

    obj.init = function(s, data) {
        selector = s;
        // Adds the svg canvas
        var svg = d3.select(selector)
            .append("svg")
                .attr("width", width + margin.left + margin.right)
                .attr("height", height + margin.top + margin.bottom)
            .append("g")
            .attr("transform", 
                  "translate(" + margin.left + "," + margin.top + ")"); 
            
        // Scale the range of the data
        x.domain(d3.extent(data, function(d) { return d.date; }));
        y.domain([0, d3.max(data, function(d) { return d.close; })]);

        // Add the valueline path.
        svg.append("path")
            .attr("class", "line")
            .attr("d", line(data));

        // Add the X Axis
        svg.append("g")
            .attr("class", "x axis")
            .attr("transform", "translate(0," + height + ")")
            .call(xAxis);

        // Add the Y Axis
        svg.append("g")
            .attr("class", "y axis")
            .call(yAxis);
            
        //Mouseover tip
        svg.call(tip);

    };
    
    
    obj.update = function(data) {
        // Scale the range of the data again 
        x.domain(d3.extent(data, function(d) { return d.date; })).nice();
        y.domain([d3.min(data, function(d) { return d.measurement; }), d3.max(data, function(d) { return d.measurement; })]);

        // Select the section we want to apply our changes to
        var svg = d3.select(selector).transition();

        // Make the changes
        svg.select(".line")   // change the line
            .duration(750)
            .attr("d", line(data));

            
        var selection = d3.select(selector).select("svg g").selectAll(".datapoint").data(data);
        selection.transition().duration(750)
          .attr('cx', function(d) { return x(d.date); })
          .attr('cy', function(d) { return y(d.measurement); });
        selection.enter().append("circle")
          .attr('class', 'datapoint')
          .attr('cx', function(d) { return x(d.date); })
          .attr('cy', function(d) { return y(d.measurement); })
          .attr('fill', 'white')
          .attr('stroke', 'steelblue')
          .attr('stroke-width', '3')
          .on('mouseover', tip.show)
          .on('mouseout', tip.hide)
          .attr("r", 0)
          .transition()
          .attr("r", 5);
        selection.exit().remove();
          
        svg.select(".x.axis") // change the x axis
            .duration(750)
            .call(xAxis);
        svg.select(".y.axis") // change the y axis
            .duration(750)
            .call(yAxis);
    };       
   
    return obj;
})();