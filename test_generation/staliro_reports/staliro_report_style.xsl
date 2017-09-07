<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:template match="/">
<html> 
<body>
  <h2>S-TaLiRo Test Execution Report</h2>
  <xsl:for-each select="staliro_test_report/test">
	  <h3>Test: <xsl:value-of select="test_id"/></h3>
	  <table border="1">
	    <tr bgcolor="#9acd32">
	      <th style="text-align:left">MATLAB Report File</th>
	      <th style="text-align:left">Req. Spec.</th>
	      <th style="text-align:left"># Runs</th>
	      <th style="text-align:left"># Tests</th>
	      <th style="text-align:left">Sim. Time (s)</th>
	      <th style="text-align:left">Messages to Send Folder</th>
	    </tr>
	    <tr>
	      <td><xsl:value-of select="matlab_report_file"/></td>
	      <td><xsl:value-of select="requirements_spec"/></td>
	      <td><xsl:value-of select="num_of_runs"/></td>
	      <td><xsl:value-of select="num_of_tests"/></td>
	      <td><xsl:value-of select="simulation_time"/></td>
	      <td><xsl:value-of select="messages_to_send_folder"/></td>
	    </tr>
	  </table>
          <h4>Saved Task Files Which are Generated by S-TaLiRo:</h4>
	  <table border="1">
	    <tr bgcolor="#9acd32">
	      <th style="text-align:left">Task File Name</th>
	      <th style="text-align:left">Path Image File</th>
	    </tr>
	    <xsl:for-each select="used_task_files/task_file">
	    <tr>
              <xsl:variable name="link" select="concat('file:///', current()/name)"/>
	      <td style="text-align:left"> <a href="{$link}"><xsl:value-of select="name"/></a></td>
              <xsl:variable name="link2image" select="concat('file:///', current()/path_image_file)"/>
	      <td style="text-align:left"> <a href="{$link2image}"><xsl:value-of select="path_image_file"/></a></td>
	    </tr>
	    </xsl:for-each>
	  </table>
          <h4>Saved Message Files Which are Changed by S-TaLiRo:</h4>
	  <table border="1">
	    <tr bgcolor="#9acd32">
	      <th style="text-align:right">Message File Name</th>
	      <th style="text-align:right">Used in Run #</th>
	    </tr>
	    <xsl:for-each select="init_cond_files/init_cond_file">
	       <xsl:for-each select="files">
    	       <tr>
                 <xsl:variable name="link" select="concat('file:///', current()/name)"/>
                 <td style="text-align:right"> <a href="{$link}"><xsl:value-of select="name"/></a></td>
	         <td style="text-align:center"><xsl:value-of select="run"/></td>
	       </tr>
	       </xsl:for-each>
	    </xsl:for-each>
	  </table>
          <h4>Initial Conditions Settings</h4>
	  <table border="1">
	    <tr bgcolor="#9acd32">
	      <th style="text-align:center">#</th>
	      <th style="text-align:center">Message File</th>
	      <th style="text-align:left">Field</th>
	      <th style="text-align:center">Limits</th>
	    </tr>
            <xsl:for-each select="initial_conditions/init_cond">
	    <tr>
	      <td style="text-align:center"><xsl:value-of select="index"/></td>
	      <td style="text-align:right"><xsl:value-of select="file_name"/></td>
	      <td><xsl:value-of select="field_name"/></td>
	      <td style="text-align:center">[<xsl:value-of select="minimum_value"/>,<xsl:value-of select="maximum_value"/>]</td>
	    </tr>
	    </xsl:for-each>
	  </table>

          <xsl:for-each select="run_reports/run">
		  <h4>Run <xsl:value-of select="position()"/>: (<xsl:value-of select="is_falsified"/>)</h4>
		  <table border="1">
		    <tr bgcolor="#9acd32">
		      <th style="text-align:left">Best Robustness</th>
		      <th style="text-align:left"># Tests</th>
		      <th style="text-align:left">Execution Time</th>
		    </tr>
		    <tr>
		      <td><xsl:value-of select="best_robustness"/></td>
		      <td><xsl:value-of select="num_of_tests"/></td>
		      <td><xsl:value-of select="execution_time"/></td>
		    </tr>
		  </table>

		  <table border="1">
		    <tr bgcolor="#9acd32">
		      <th style="text-align:center">Initial Condition #</th>
		      <th style="text-align:center">File</th>
		      <th style="text-align:left">Field</th>
		      <th style="text-align:center">Value</th>
		    </tr>
		    <xsl:for-each select="initial_condition_values/init_cond">
		    <tr>
		      <td style="text-align:center"><xsl:value-of select="position()"/></td>
		      <td style="text-align:right"><xsl:value-of select="File"/></td>
		      <td><xsl:value-of select="Field"/></td>
		      <td style="text-align:right"><xsl:value-of select="Value"/></td>
		    </tr>
		    </xsl:for-each>
		  </table>
          </xsl:for-each>
  </xsl:for-each>
<footnote label="1"><br></br>This report is auto generated by <a href="https://sites.google.com/a/asu.edu/s-taliro/s-taliro">S-TaLiRo</a> at <xsl:value-of select="staliro_test_report/report_generation_time"/>.<br></br>--- END OF REPORT ---</footnote>
</body>
</html>
</xsl:template>
</xsl:stylesheet>


