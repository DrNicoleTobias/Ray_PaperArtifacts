<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="7.5.0">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="50" name="dxf" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="53" name="tGND_GNDA" color="7" fill="9" visible="no" active="no"/>
<layer number="54" name="bGND_GNDA" color="1" fill="9" visible="no" active="no"/>
<layer number="56" name="wert" color="7" fill="1" visible="no" active="no"/>
<layer number="57" name="tCAD" color="7" fill="1" visible="no" active="no"/>
<layer number="59" name="tCarbon" color="7" fill="1" visible="no" active="no"/>
<layer number="60" name="bCarbon" color="7" fill="1" visible="no" active="no"/>
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
<layer number="99" name="SpiceOrder" color="5" fill="1" visible="no" active="no"/>
<layer number="100" name="Muster" color="7" fill="1" visible="no" active="no"/>
<layer number="101" name="Patch_Top" color="12" fill="4" visible="yes" active="yes"/>
<layer number="102" name="Vscore" color="7" fill="1" visible="yes" active="yes"/>
<layer number="103" name="tMap" color="7" fill="1" visible="yes" active="yes"/>
<layer number="104" name="Name" color="16" fill="1" visible="yes" active="yes"/>
<layer number="105" name="tPlate" color="7" fill="1" visible="yes" active="yes"/>
<layer number="106" name="bPlate" color="7" fill="1" visible="yes" active="yes"/>
<layer number="107" name="Crop" color="7" fill="1" visible="yes" active="yes"/>
<layer number="108" name="fp8" color="7" fill="1" visible="yes" active="yes"/>
<layer number="109" name="fp9" color="7" fill="1" visible="yes" active="yes"/>
<layer number="110" name="fp0" color="7" fill="1" visible="yes" active="yes"/>
<layer number="111" name="LPC17xx" color="7" fill="1" visible="yes" active="yes"/>
<layer number="112" name="tSilk" color="7" fill="1" visible="yes" active="yes"/>
<layer number="113" name="IDFDebug" color="7" fill="1" visible="yes" active="yes"/>
<layer number="114" name="Badge_Outline" color="7" fill="1" visible="yes" active="yes"/>
<layer number="115" name="ReferenceISLANDS" color="7" fill="1" visible="yes" active="yes"/>
<layer number="116" name="Patch_BOT" color="9" fill="4" visible="yes" active="yes"/>
<layer number="118" name="Rect_Pads" color="7" fill="1" visible="yes" active="yes"/>
<layer number="121" name="_tsilk" color="7" fill="1" visible="yes" active="yes"/>
<layer number="122" name="_bsilk" color="7" fill="1" visible="yes" active="yes"/>
<layer number="123" name="tTestmark" color="7" fill="1" visible="yes" active="yes"/>
<layer number="124" name="bTestmark" color="7" fill="1" visible="yes" active="yes"/>
<layer number="125" name="_tNames" color="7" fill="1" visible="yes" active="yes"/>
<layer number="126" name="_bNames" color="7" fill="1" visible="yes" active="yes"/>
<layer number="127" name="_tValues" color="7" fill="1" visible="yes" active="yes"/>
<layer number="128" name="_bValues" color="7" fill="1" visible="yes" active="yes"/>
<layer number="129" name="Mask" color="7" fill="1" visible="yes" active="yes"/>
<layer number="130" name="130bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="131" name="tAdjust" color="7" fill="1" visible="yes" active="yes"/>
<layer number="132" name="bAdjust" color="7" fill="1" visible="yes" active="yes"/>
<layer number="144" name="Drill_legend" color="7" fill="1" visible="yes" active="yes"/>
<layer number="145" name="DrillLegend_01-16" color="7" fill="1" visible="yes" active="yes"/>
<layer number="150" name="Notes" color="7" fill="1" visible="yes" active="yes"/>
<layer number="151" name="HeatSink" color="7" fill="1" visible="yes" active="yes"/>
<layer number="152" name="_bDocu" color="7" fill="1" visible="yes" active="yes"/>
<layer number="153" name="FabDoc1" color="6" fill="1" visible="no" active="no"/>
<layer number="154" name="FabDoc2" color="2" fill="1" visible="no" active="no"/>
<layer number="155" name="FabDoc3" color="7" fill="15" visible="no" active="no"/>
<layer number="199" name="Contour" color="7" fill="1" visible="yes" active="yes"/>
<layer number="200" name="200bmp" color="1" fill="10" visible="yes" active="yes"/>
<layer number="201" name="201bmp" color="1" fill="10" visible="yes" active="yes"/>
<layer number="202" name="202bmp" color="3" fill="10" visible="yes" active="yes"/>
<layer number="203" name="203bmp" color="4" fill="10" visible="yes" active="yes"/>
<layer number="204" name="204bmp" color="5" fill="10" visible="yes" active="yes"/>
<layer number="205" name="205bmp" color="6" fill="10" visible="yes" active="yes"/>
<layer number="206" name="206bmp" color="7" fill="10" visible="yes" active="yes"/>
<layer number="207" name="207bmp" color="8" fill="10" visible="yes" active="yes"/>
<layer number="208" name="208bmp" color="9" fill="10" visible="yes" active="yes"/>
<layer number="209" name="209bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="210" name="210bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="211" name="211bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="212" name="212bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="213" name="213bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="214" name="214bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="215" name="215bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="216" name="216bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="217" name="217bmp" color="18" fill="1" visible="no" active="no"/>
<layer number="218" name="218bmp" color="19" fill="1" visible="no" active="no"/>
<layer number="219" name="219bmp" color="20" fill="1" visible="no" active="no"/>
<layer number="220" name="220bmp" color="21" fill="1" visible="no" active="no"/>
<layer number="221" name="221bmp" color="22" fill="1" visible="no" active="no"/>
<layer number="222" name="222bmp" color="23" fill="1" visible="no" active="no"/>
<layer number="223" name="223bmp" color="24" fill="1" visible="no" active="no"/>
<layer number="224" name="224bmp" color="25" fill="1" visible="no" active="no"/>
<layer number="225" name="225bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="226" name="226bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="227" name="227bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="228" name="228bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="229" name="229bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="230" name="230bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="231" name="Eagle3D_PG1" color="7" fill="1" visible="yes" active="yes"/>
<layer number="232" name="Eagle3D_PG2" color="7" fill="1" visible="yes" active="yes"/>
<layer number="233" name="Eagle3D_PG3" color="7" fill="1" visible="yes" active="yes"/>
<layer number="248" name="Housing" color="7" fill="1" visible="yes" active="yes"/>
<layer number="249" name="Edge" color="7" fill="1" visible="yes" active="yes"/>
<layer number="250" name="Descript" color="3" fill="1" visible="no" active="no"/>
<layer number="251" name="SMDround" color="12" fill="11" visible="no" active="no"/>
<layer number="254" name="cooling" color="7" fill="1" visible="yes" active="yes"/>
<layer number="255" name="255robobuzz" color="7" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="cc1101">
<packages>
<package name="QLP20">
<circle x="-1.5882625" y="1.5882625" radius="0.0424" width="0.127" layer="21"/>
<wire x1="-1.85" y1="2" x2="1.85" y2="2" width="0.127" layer="48"/>
<wire x1="1.85" y1="2" x2="2" y2="1.85" width="0.127" layer="48"/>
<wire x1="2" y1="1.85" x2="2" y2="-1.85" width="0.127" layer="48"/>
<wire x1="2" y1="-1.85" x2="1.85" y2="-2" width="0.127" layer="48"/>
<wire x1="1.85" y1="-2" x2="-1.85" y2="-2" width="0.127" layer="48"/>
<wire x1="-1.85" y1="-2" x2="-2" y2="-1.85" width="0.127" layer="48"/>
<wire x1="-2" y1="-1.85" x2="-2" y2="1.85" width="0.127" layer="48"/>
<wire x1="-2" y1="1.85" x2="-1.85" y2="2" width="0.127" layer="48"/>
<rectangle x1="-0.325" y1="0.65" x2="0.325" y2="1.05" layer="31"/>
<rectangle x1="-1.175" y1="-0.2" x2="-0.525" y2="0.2" layer="31" rot="R90"/>
<rectangle x1="0.525" y1="-0.2" x2="1.175" y2="0.2" layer="31" rot="R90"/>
<rectangle x1="-0.325" y1="-1.05" x2="0.325" y2="-0.65" layer="31"/>
<rectangle x1="-1.905" y1="-1.905" x2="1.905" y2="1.905" layer="39"/>
<smd name="1" x="-1.88" y="1" dx="0.96" dy="0.28" layer="1"/>
<smd name="2" x="-1.88" y="0.5" dx="0.96" dy="0.28" layer="1"/>
<smd name="3" x="-1.88" y="0" dx="0.96" dy="0.28" layer="1"/>
<smd name="4" x="-1.88" y="-0.5" dx="0.96" dy="0.28" layer="1"/>
<smd name="5" x="-1.88" y="-1" dx="0.96" dy="0.28" layer="1"/>
<smd name="6" x="-1" y="-1.88" dx="0.96" dy="0.28" layer="1" rot="R90"/>
<smd name="7" x="-0.5" y="-1.88" dx="0.96" dy="0.28" layer="1" rot="R90"/>
<smd name="8" x="0" y="-1.88" dx="0.96" dy="0.28" layer="1" rot="R90"/>
<smd name="9" x="0.5" y="-1.88" dx="0.96" dy="0.28" layer="1" rot="R90"/>
<smd name="10" x="1" y="-1.88" dx="0.96" dy="0.28" layer="1" rot="R90"/>
<smd name="11" x="1.88" y="-1" dx="0.96" dy="0.28" layer="1" rot="R180"/>
<smd name="12" x="1.88" y="-0.5" dx="0.96" dy="0.28" layer="1" rot="R180"/>
<smd name="13" x="1.88" y="0" dx="0.96" dy="0.28" layer="1" rot="R180"/>
<smd name="14" x="1.88" y="0.5" dx="0.96" dy="0.28" layer="1" rot="R180"/>
<smd name="15" x="1.88" y="1" dx="0.96" dy="0.28" layer="1" rot="R180"/>
<smd name="16" x="1" y="1.88" dx="0.96" dy="0.28" layer="1" rot="R270"/>
<smd name="17" x="0.5" y="1.88" dx="0.96" dy="0.28" layer="1" rot="R270"/>
<smd name="18" x="0" y="1.88" dx="0.96" dy="0.28" layer="1" rot="R270"/>
<smd name="19" x="-0.5" y="1.88" dx="0.96" dy="0.28" layer="1" rot="R270"/>
<smd name="20" x="-1" y="1.88" dx="0.96" dy="0.28" layer="1" rot="R270"/>
<smd name="GND" x="0" y="0" dx="2.4" dy="2.4" layer="1" cream="no"/>
<pad name="GND1" x="0" y="0" drill="0.332740625" stop="no" thermals="no"/>
<pad name="GND2" x="-0.635" y="0.635" drill="0.332740625" stop="no" thermals="no"/>
<pad name="GND3" x="0.635" y="0.635" drill="0.332740625" stop="no" thermals="no"/>
<pad name="GND4" x="-0.635" y="-0.635" drill="0.332740625" stop="no" thermals="no"/>
<pad name="GND5" x="0.635" y="-0.635" drill="0.332740625" stop="no" thermals="no"/>
<text x="-2" y="2.5" size="1" layer="25" font="vector" ratio="10">&gt;NAME</text>
<text x="0" y="-2.54" size="1" layer="27" font="vector" ratio="10" align="top-center">&gt;VALUE</text>
<wire x1="-1.3" y1="2" x2="-2" y2="2" width="0.127" layer="21"/>
<wire x1="-2" y1="2" x2="-2" y2="1.3" width="0.127" layer="21"/>
<wire x1="1.3" y1="2" x2="2" y2="2" width="0.127" layer="21"/>
<wire x1="2" y1="2" x2="2" y2="1.3" width="0.127" layer="21"/>
<wire x1="2" y1="-1.3" x2="2" y2="-2" width="0.127" layer="21"/>
<wire x1="2" y1="-2" x2="1.3" y2="-2" width="0.127" layer="21"/>
<wire x1="-1.3" y1="-2" x2="-2" y2="-2" width="0.127" layer="21"/>
<wire x1="-2" y1="-2" x2="-2" y2="-1.3" width="0.127" layer="21"/>
</package>
<package name="XTAL-3.2X2.5">
<wire x1="1.9" y1="-1.5" x2="-1.9" y2="-1.5" width="0.17" layer="48"/>
<wire x1="-1.9" y1="-1.5" x2="-1.9" y2="1.5" width="0.17" layer="48"/>
<smd name="1" x="-1.1" y="-0.8" dx="1.4" dy="1.2" layer="1"/>
<smd name="2" x="1.1" y="-0.8" dx="1.4" dy="1.2" layer="1"/>
<smd name="3" x="1.1" y="0.8" dx="1.4" dy="1.2" layer="1"/>
<smd name="4" x="-1.1" y="0.8" dx="1.4" dy="1.2" layer="1"/>
<text x="-2.6" y="1.7" size="1.27" layer="25">&gt;NAME</text>
</package>
</packages>
<symbols>
<symbol name="CC1101">
<wire x1="-17.78" y1="-25.4" x2="-17.78" y2="25.4" width="0.254" layer="94"/>
<wire x1="-17.78" y1="25.4" x2="17.78" y2="25.4" width="0.254" layer="94"/>
<wire x1="17.78" y1="25.4" x2="17.78" y2="-25.4" width="0.254" layer="94"/>
<wire x1="17.78" y1="-25.4" x2="-17.78" y2="-25.4" width="0.254" layer="94"/>
<pin name="AVDD1" x="20.32" y="22.86" visible="pin" length="short" rot="R180"/>
<pin name="AVDD2" x="20.32" y="17.78" visible="pin" length="short" rot="R180"/>
<pin name="AVDD3" x="20.32" y="12.7" visible="pin" length="short" rot="R180"/>
<pin name="AVDD4" x="20.32" y="7.62" visible="pin" length="short" rot="R180"/>
<pin name="CSN" x="-20.32" y="-7.62" visible="pin" length="short"/>
<pin name="DCOUPL" x="-20.32" y="-2.54" visible="pin" length="short"/>
<pin name="DGUARD" x="-20.32" y="-12.7" visible="pin" length="short"/>
<pin name="DVDD" x="-20.32" y="2.54" visible="pin" length="short"/>
<pin name="GDO0(ATEST)" x="-20.32" y="-17.78" visible="pin" length="short"/>
<pin name="GDO2" x="-20.32" y="12.7" visible="pin" length="short"/>
<pin name="GND" x="20.32" y="-22.86" visible="pin" length="short" rot="R180"/>
<pin name="RBIAS" x="20.32" y="2.54" visible="pin" length="short" rot="R180"/>
<pin name="RF_N" x="20.32" y="-2.54" visible="pin" length="short" rot="R180"/>
<pin name="RF_P" x="20.32" y="-7.62" visible="pin" length="short" rot="R180"/>
<pin name="SCLK" x="-20.32" y="22.86" visible="pin" length="short"/>
<pin name="SI" x="-20.32" y="7.62" visible="pin" length="short"/>
<pin name="SO(GDO1)" x="-20.32" y="17.78" visible="pin" length="short"/>
<pin name="XOSC_Q1" x="20.32" y="-17.78" visible="pin" length="short" rot="R180"/>
<pin name="XOSC_Q2" x="20.32" y="-12.7" visible="pin" length="short" rot="R180"/>
<text x="-17.78" y="26.67" size="2.54" layer="95" font="vector" ratio="10">&gt;NAME</text>
<text x="0" y="0" size="2.54" layer="96" font="vector" ratio="15" align="center">&gt;VALUE</text>
</symbol>
<symbol name="XTAL">
<wire x1="1.016" y1="0" x2="2.54" y2="0" width="0.1524" layer="94"/>
<wire x1="-2.54" y1="0" x2="-1.016" y2="0" width="0.1524" layer="94"/>
<wire x1="-0.381" y1="1.524" x2="-0.381" y2="-1.524" width="0.254" layer="94"/>
<wire x1="-0.381" y1="-1.524" x2="0.381" y2="-1.524" width="0.254" layer="94"/>
<wire x1="0.381" y1="-1.524" x2="0.381" y2="1.524" width="0.254" layer="94"/>
<wire x1="0.381" y1="1.524" x2="-0.381" y2="1.524" width="0.254" layer="94"/>
<wire x1="1.016" y1="1.778" x2="1.016" y2="-1.778" width="0.254" layer="94"/>
<wire x1="-1.016" y1="1.778" x2="-1.016" y2="-1.778" width="0.254" layer="94"/>
<pin name="1" x="-2.54" y="0" visible="off" length="point" direction="pas" swaplevel="1"/>
<pin name="2" x="2.54" y="0" visible="off" length="point" direction="pas" swaplevel="1" rot="R180"/>
<text x="-2.54" y="2.54" size="1.778" layer="96">&gt;VALUE</text>
<text x="-2.159" y="-1.143" size="0.8636" layer="93">1</text>
<text x="1.524" y="-1.143" size="0.8636" layer="93">2</text>
<text x="-2.54" y="5.08" size="1.778" layer="95">&gt;NAME</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="CC1101" prefix="IC">
<gates>
<gate name="G$1" symbol="CC1101" x="0" y="0"/>
</gates>
<devices>
<device name="" package="QLP20">
<connects>
<connect gate="G$1" pin="AVDD1" pad="9"/>
<connect gate="G$1" pin="AVDD2" pad="11"/>
<connect gate="G$1" pin="AVDD3" pad="14"/>
<connect gate="G$1" pin="AVDD4" pad="15"/>
<connect gate="G$1" pin="CSN" pad="7"/>
<connect gate="G$1" pin="DCOUPL" pad="5"/>
<connect gate="G$1" pin="DGUARD" pad="18"/>
<connect gate="G$1" pin="DVDD" pad="4"/>
<connect gate="G$1" pin="GDO0(ATEST)" pad="6"/>
<connect gate="G$1" pin="GDO2" pad="3"/>
<connect gate="G$1" pin="GND" pad="16 19 GND GND1 GND2 GND3 GND4 GND5"/>
<connect gate="G$1" pin="RBIAS" pad="17"/>
<connect gate="G$1" pin="RF_N" pad="13"/>
<connect gate="G$1" pin="RF_P" pad="12"/>
<connect gate="G$1" pin="SCLK" pad="1"/>
<connect gate="G$1" pin="SI" pad="20"/>
<connect gate="G$1" pin="SO(GDO1)" pad="2"/>
<connect gate="G$1" pin="XOSC_Q1" pad="8"/>
<connect gate="G$1" pin="XOSC_Q2" pad="10"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="XTAL" prefix="X">
<gates>
<gate name="G$1" symbol="XTAL" x="0" y="0"/>
</gates>
<devices>
<device name="-3.2X2.5" package="XTAL-3.2X2.5">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="3"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="johanson-baluns">
<packages>
<package name="XXXXBM15A0001">
<wire x1="1.016" y1="1.524" x2="-1.016" y2="1.524" width="0.127" layer="48"/>
<wire x1="-1.016" y1="1.524" x2="-1.016" y2="-1.524" width="0.127" layer="48"/>
<wire x1="-1.016" y1="-1.524" x2="1.016" y2="-1.524" width="0.127" layer="48"/>
<wire x1="1.016" y1="-1.524" x2="1.016" y2="1.524" width="0.127" layer="48"/>
<wire x1="1.016" y1="1.524" x2="1.27" y2="1.778" width="0.127" layer="21"/>
<rectangle x1="-1.016" y1="-1.524" x2="1.016" y2="1.524" layer="39"/>
<smd name="1" x="0.65" y="0.8" dx="0.33" dy="0.9" layer="1"/>
<smd name="2" x="0" y="0.8" dx="0.33" dy="0.9" layer="1"/>
<smd name="3" x="-0.65" y="0.8" dx="0.33" dy="0.9" layer="1"/>
<smd name="4" x="-0.65" y="-0.8" dx="0.33" dy="0.9" layer="1"/>
<smd name="5" x="0" y="-0.8" dx="0.33" dy="0.9" layer="1"/>
<smd name="6" x="0.65" y="-0.8" dx="0.33" dy="0.9" layer="1"/>
<text x="-0.635" y="1.905" size="1" layer="25" font="vector" ratio="10">&gt;NAME</text>
</package>
</packages>
<symbols>
<symbol name="BALUN_CC110X">
<wire x1="-15.24" y1="7.62" x2="15.24" y2="7.62" width="0.254" layer="94"/>
<wire x1="15.24" y1="7.62" x2="15.24" y2="-7.62" width="0.254" layer="94"/>
<wire x1="15.24" y1="-7.62" x2="-15.24" y2="-7.62" width="0.254" layer="94"/>
<wire x1="-15.24" y1="-7.62" x2="-15.24" y2="7.62" width="0.254" layer="94"/>
<pin name="BAL3" x="-17.78" y="5.08" visible="pin" length="short"/>
<pin name="BAL4" x="-17.78" y="-5.08" visible="pin" length="short"/>
<pin name="GND" x="17.78" y="-5.08" visible="pin" length="short" rot="R180"/>
<pin name="UNBAL" x="17.78" y="5.08" visible="pin" length="short" rot="R180"/>
<text x="-15.24" y="8.89" size="2.54" layer="95" font="vector">&gt;NAME</text>
<text x="0" y="0" size="2.54" layer="96" font="vector" ratio="15" align="center">&gt;VALUE</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="0896BM15A0001" prefix="U">
<description>868/915 MHz Impedance Matched/Balun/LPF Integrated Component for T.I. CC110X,
CC111X, CC113X and CC115X, CC110L, CC113L, CC115L, CC430 and RF430</description>
<gates>
<gate name="G$1" symbol="BALUN_CC110X" x="0" y="0"/>
</gates>
<devices>
<device name="" package="XXXXBM15A0001">
<connects>
<connect gate="G$1" pin="BAL3" pad="3"/>
<connect gate="G$1" pin="BAL4" pad="4"/>
<connect gate="G$1" pin="GND" pad="2 5 6" route="any"/>
<connect gate="G$1" pin="UNBAL" pad="1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="HF-Bauteile">
<packages>
<package name="ANT-433-USP">
<smd name="S1" x="-6" y="0" dx="4" dy="0.8" layer="1" rot="R90"/>
<wire x1="-6.15" y1="2.2" x2="6.15" y2="2.2" width="0.127" layer="21"/>
<wire x1="6.15" y1="2" x2="6.15" y2="-2" width="0.127" layer="51"/>
<wire x1="6.15" y1="-2.2" x2="-6.15" y2="-2.2" width="0.127" layer="21"/>
<wire x1="-6.15" y1="-2" x2="-6.15" y2="2" width="0.127" layer="51"/>
<smd name="P$4" x="6" y="0" dx="4" dy="0.8" layer="1" rot="R90"/>
<text x="0" y="0" size="1.016" layer="21" align="center">YAGEO S432</text>
<text x="-4.5" y="-1.5" size="0.6096" layer="21" align="center">S1</text>
</package>
</packages>
<symbols>
<symbol name="CHIP_ANT_MURATA">
<wire x1="0" y1="2.54" x2="25.4" y2="2.54" width="0.254" layer="94"/>
<wire x1="25.4" y1="2.54" x2="25.4" y2="-2.54" width="0.254" layer="94"/>
<wire x1="25.4" y1="-2.54" x2="0" y2="-2.54" width="0.254" layer="94"/>
<wire x1="0" y1="-2.54" x2="0" y2="2.54" width="0.254" layer="94"/>
<wire x1="0.762" y1="0" x2="22.606" y2="0" width="0.254" layer="94"/>
<wire x1="22.606" y1="0" x2="24.13" y2="1.524" width="0.254" layer="94"/>
<wire x1="22.606" y1="0" x2="24.13" y2="-1.524" width="0.254" layer="94"/>
<pin name="P$1" x="-5.08" y="0" length="middle"/>
<text x="0.254" y="3.302" size="1.27" layer="95">&gt;Name</text>
<text x="0" y="-4.318" size="1.27" layer="96">&gt;Value</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="433CHIP">
<gates>
<gate name="G$1" symbol="CHIP_ANT_MURATA" x="-12.7" y="0"/>
</gates>
<devices>
<device name="" package="ANT-433-USP">
<connects>
<connect gate="G$1" pin="P$1" pad="S1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="supply1">
<description>&lt;b&gt;Supply Symbols&lt;/b&gt;&lt;p&gt;
 GND, VCC, 0V, +5V, -5V, etc.&lt;p&gt;
 Please keep in mind, that these devices are necessary for the
 automatic wiring of the supply signals.&lt;p&gt;
 The pin name defined in the symbol is identical to the net which is to be wired automatically.&lt;p&gt;
 In this library the device names are the same as the pin names of the symbols, therefore the correct signal names appear next to the supply symbols in the schematic.&lt;p&gt;
 &lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
</packages>
<symbols>
<symbol name="GND">
<wire x1="-1.905" y1="0" x2="1.905" y2="0" width="0.254" layer="94"/>
<text x="-2.54" y="-2.54" size="1.778" layer="96">&gt;VALUE</text>
<pin name="GND" x="0" y="2.54" visible="off" length="short" direction="sup" rot="R270"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="GND" prefix="GND">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="1" symbol="GND" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="tiny_passives">
<packages>
<package name="0402">
<wire x1="-0.49" y1="0.2" x2="-0.49" y2="-0.2" width="0.127" layer="51"/>
<wire x1="-0.49" y1="-0.2" x2="0.56" y2="-0.2" width="0.127" layer="51"/>
<wire x1="0.56" y1="-0.2" x2="0.56" y2="0.2" width="0.127" layer="51"/>
<wire x1="0.56" y1="0.2" x2="-0.49" y2="0.2" width="0.127" layer="51"/>
<smd name="1" x="-0.49" y="0" dx="0.6" dy="0.6" layer="1" rot="R180"/>
<smd name="2" x="0.51" y="0" dx="0.6" dy="0.6" layer="1" rot="R180"/>
<text x="-0.64" y="0.4" size="0.254" layer="25">&gt;NAME</text>
<text x="-0.69" y="-0.6" size="0.254" layer="27">&gt;VALUE</text>
</package>
<package name="0603">
<smd name="1" x="-0.85" y="0" dx="1.2" dy="1.1" layer="1"/>
<smd name="2" x="0.85" y="0" dx="1.2" dy="1.1" layer="1"/>
<wire x1="0" y1="0.3" x2="0" y2="-0.3" width="0.127" layer="51"/>
<wire x1="-0.9" y1="0.4" x2="1" y2="0.4" width="0.254" layer="51"/>
<wire x1="1" y1="0.4" x2="1" y2="-0.4" width="0.254" layer="51"/>
<wire x1="1" y1="-0.4" x2="-0.9" y2="-0.4" width="0.254" layer="51"/>
<wire x1="-0.9" y1="-0.4" x2="-0.9" y2="0.4" width="0.254" layer="51"/>
<text x="-1.27" y="0.635" size="0.254" layer="25">&gt;NAME</text>
<text x="-1.27" y="-0.889" size="0.254" layer="27">&gt;VALUE</text>
</package>
</packages>
<symbols>
<symbol name="C-EU">
<wire x1="0" y1="0" x2="0" y2="-0.508" width="0.1524" layer="94"/>
<wire x1="0" y1="-2.54" x2="0" y2="-2.032" width="0.1524" layer="94"/>
<text x="1.524" y="0.381" size="1.778" layer="95">&gt;NAME</text>
<text x="1.524" y="-4.699" size="1.778" layer="96">&gt;VALUE</text>
<rectangle x1="-2.032" y1="-2.032" x2="2.032" y2="-1.524" layer="94"/>
<rectangle x1="-2.032" y1="-1.016" x2="2.032" y2="-0.508" layer="94"/>
<pin name="1" x="0" y="2.54" visible="off" length="short" direction="pas" swaplevel="1" rot="R270"/>
<pin name="2" x="0" y="-5.08" visible="off" length="short" direction="pas" swaplevel="1" rot="R90"/>
</symbol>
<symbol name="R-EU">
<wire x1="-2.54" y1="0" x2="-2.159" y2="1.016" width="0.1524" layer="94"/>
<wire x1="-2.159" y1="1.016" x2="-1.524" y2="-1.016" width="0.1524" layer="94"/>
<wire x1="-1.524" y1="-1.016" x2="-0.889" y2="1.016" width="0.1524" layer="94"/>
<wire x1="-0.889" y1="1.016" x2="-0.254" y2="-1.016" width="0.1524" layer="94"/>
<wire x1="-0.254" y1="-1.016" x2="0.381" y2="1.016" width="0.1524" layer="94"/>
<wire x1="0.381" y1="1.016" x2="1.016" y2="-1.016" width="0.1524" layer="94"/>
<wire x1="1.016" y1="-1.016" x2="1.651" y2="1.016" width="0.1524" layer="94"/>
<wire x1="1.651" y1="1.016" x2="2.286" y2="-1.016" width="0.1524" layer="94"/>
<wire x1="2.286" y1="-1.016" x2="2.54" y2="0" width="0.1524" layer="94"/>
<text x="-3.81" y="1.4986" size="1.778" layer="95">&gt;NAME</text>
<text x="-3.81" y="-3.302" size="1.778" layer="96">&gt;VALUE</text>
<pin name="2" x="5.08" y="0" visible="off" length="short" direction="pas" swaplevel="1" rot="R180"/>
<pin name="1" x="-5.08" y="0" visible="off" length="short" direction="pas" swaplevel="1"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="C-EU" prefix="C" uservalue="yes">
<gates>
<gate name="C1" symbol="C-EU" x="0" y="0"/>
</gates>
<devices>
<device name="" package="0402">
<connects>
<connect gate="C1" pin="1" pad="1"/>
<connect gate="C1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="0603" package="0603">
<connects>
<connect gate="C1" pin="1" pad="1"/>
<connect gate="C1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="R-EU" prefix="R" uservalue="yes">
<gates>
<gate name="R1" symbol="R-EU" x="0" y="0"/>
</gates>
<devices>
<device name="" package="0402">
<connects>
<connect gate="R1" pin="1" pad="1"/>
<connect gate="R1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="0603" package="0603">
<connects>
<connect gate="R1" pin="1" pad="1"/>
<connect gate="R1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="SparkFun-Connectors">
<description>&lt;h3&gt;SparkFun Electronics' preferred foot prints&lt;/h3&gt;
In this library you'll find connectors and sockets- basically anything that can be plugged into or onto.&lt;br&gt;&lt;br&gt;
We've spent an enormous amount of time creating and checking these footprints and parts, but it is the end user's responsibility to ensure correctness and suitablity for a given componet or application. If you enjoy using this library, please buy one of our products at www.sparkfun.com.
&lt;br&gt;&lt;br&gt;
&lt;b&gt;Licensing:&lt;/b&gt; Creative Commons ShareAlike 4.0 International - https://creativecommons.org/licenses/by-sa/4.0/ 
&lt;br&gt;&lt;br&gt;
You are welcome to use this library for commercial purposes. For attribution, we ask that when you begin to sell your device using our footprint, you email us with a link to the product being sold. We want bragging rights that we helped (in a very small part) to create your 8th world wonder. We would like the opportunity to feature your device on our homepage.</description>
<packages>
<package name="1X04">
<wire x1="6.985" y1="1.27" x2="8.255" y2="1.27" width="0.2032" layer="21"/>
<wire x1="8.255" y1="1.27" x2="8.89" y2="0.635" width="0.2032" layer="21"/>
<wire x1="8.89" y1="-0.635" x2="8.255" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="3.81" y1="0.635" x2="4.445" y2="1.27" width="0.2032" layer="21"/>
<wire x1="4.445" y1="1.27" x2="5.715" y2="1.27" width="0.2032" layer="21"/>
<wire x1="5.715" y1="1.27" x2="6.35" y2="0.635" width="0.2032" layer="21"/>
<wire x1="6.35" y1="-0.635" x2="5.715" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="5.715" y1="-1.27" x2="4.445" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="4.445" y1="-1.27" x2="3.81" y2="-0.635" width="0.2032" layer="21"/>
<wire x1="6.985" y1="1.27" x2="6.35" y2="0.635" width="0.2032" layer="21"/>
<wire x1="6.35" y1="-0.635" x2="6.985" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="8.255" y1="-1.27" x2="6.985" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="-0.635" y1="1.27" x2="0.635" y2="1.27" width="0.2032" layer="21"/>
<wire x1="0.635" y1="1.27" x2="1.27" y2="0.635" width="0.2032" layer="21"/>
<wire x1="1.27" y1="-0.635" x2="0.635" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="1.27" y1="0.635" x2="1.905" y2="1.27" width="0.2032" layer="21"/>
<wire x1="1.905" y1="1.27" x2="3.175" y2="1.27" width="0.2032" layer="21"/>
<wire x1="3.175" y1="1.27" x2="3.81" y2="0.635" width="0.2032" layer="21"/>
<wire x1="3.81" y1="-0.635" x2="3.175" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="3.175" y1="-1.27" x2="1.905" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="1.905" y1="-1.27" x2="1.27" y2="-0.635" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="0.635" x2="-1.27" y2="-0.635" width="0.2032" layer="21"/>
<wire x1="-0.635" y1="1.27" x2="-1.27" y2="0.635" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="-0.635" x2="-0.635" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="0.635" y1="-1.27" x2="-0.635" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="8.89" y1="0.635" x2="8.89" y2="-0.635" width="0.2032" layer="21"/>
<pad name="1" x="0" y="0" drill="1.016" diameter="1.8796" shape="square" rot="R90"/>
<pad name="2" x="2.54" y="0" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="3" x="5.08" y="0" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="4" x="7.62" y="0" drill="1.016" diameter="1.8796" rot="R90"/>
<text x="-1.3462" y="1.8288" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-1.27" y="-3.175" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="7.366" y1="-0.254" x2="7.874" y2="0.254" layer="51"/>
<rectangle x1="4.826" y1="-0.254" x2="5.334" y2="0.254" layer="51"/>
<rectangle x1="2.286" y1="-0.254" x2="2.794" y2="0.254" layer="51"/>
<rectangle x1="-0.254" y1="-0.254" x2="0.254" y2="0.254" layer="51"/>
</package>
<package name="MOLEX-1X4">
<wire x1="-1.27" y1="3.048" x2="-1.27" y2="-2.54" width="0.127" layer="21"/>
<wire x1="8.89" y1="3.048" x2="8.89" y2="-2.54" width="0.127" layer="21"/>
<wire x1="8.89" y1="3.048" x2="-1.27" y2="3.048" width="0.127" layer="21"/>
<wire x1="8.89" y1="-2.54" x2="7.62" y2="-2.54" width="0.127" layer="21"/>
<wire x1="7.62" y1="-2.54" x2="0" y2="-2.54" width="0.127" layer="21"/>
<wire x1="0" y1="-2.54" x2="-1.27" y2="-2.54" width="0.127" layer="21"/>
<wire x1="0" y1="-2.54" x2="0" y2="-1.27" width="0.127" layer="21"/>
<wire x1="0" y1="-1.27" x2="7.62" y2="-1.27" width="0.127" layer="21"/>
<wire x1="7.62" y1="-1.27" x2="7.62" y2="-2.54" width="0.127" layer="21"/>
<pad name="1" x="0" y="0" drill="1.016" diameter="1.8796" shape="square"/>
<pad name="2" x="2.54" y="0" drill="1.016" diameter="1.8796"/>
<pad name="3" x="5.08" y="0" drill="1.016" diameter="1.8796"/>
<pad name="4" x="7.62" y="0" drill="1.016" diameter="1.8796"/>
</package>
<package name="SCREWTERMINAL-3.5MM-4">
<wire x1="-1.75" y1="3.4" x2="12.25" y2="3.4" width="0.2032" layer="21"/>
<wire x1="12.25" y1="3.4" x2="12.25" y2="-2.8" width="0.2032" layer="21"/>
<wire x1="12.25" y1="-2.8" x2="12.25" y2="-3.6" width="0.2032" layer="21"/>
<wire x1="12.25" y1="-3.6" x2="-1.75" y2="-3.6" width="0.2032" layer="21"/>
<wire x1="-1.75" y1="-3.6" x2="-1.75" y2="-2.8" width="0.2032" layer="21"/>
<wire x1="-1.75" y1="-2.8" x2="-1.75" y2="3.4" width="0.2032" layer="21"/>
<wire x1="12.25" y1="-2.8" x2="-1.75" y2="-2.8" width="0.2032" layer="21"/>
<wire x1="-1.75" y1="-1.35" x2="-2.25" y2="-1.35" width="0.2032" layer="51"/>
<wire x1="-2.25" y1="-1.35" x2="-2.25" y2="-2.35" width="0.2032" layer="51"/>
<wire x1="-2.25" y1="-2.35" x2="-1.75" y2="-2.35" width="0.2032" layer="51"/>
<wire x1="12.25" y1="3.15" x2="12.75" y2="3.15" width="0.2032" layer="51"/>
<wire x1="12.75" y1="3.15" x2="12.75" y2="2.15" width="0.2032" layer="51"/>
<wire x1="12.75" y1="2.15" x2="12.25" y2="2.15" width="0.2032" layer="51"/>
<circle x="0" y="0" radius="0.425" width="0.001" layer="51"/>
<circle x="3.5" y="0" radius="0.425" width="0.001" layer="51"/>
<circle x="7" y="0" radius="0.425" width="0.001" layer="51"/>
<circle x="10.5" y="0" radius="0.425" width="0.001" layer="51"/>
<pad name="1" x="0" y="0" drill="1.2" diameter="2.032" shape="square"/>
<pad name="2" x="3.5" y="0" drill="1.2" diameter="2.032"/>
<pad name="3" x="7" y="0" drill="1.2" diameter="2.032"/>
<pad name="4" x="10.5" y="0" drill="1.2" diameter="2.032"/>
<text x="-1.27" y="2.54" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.27" y="1.27" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="1X04-1.27MM">
<wire x1="-0.381" y1="-0.889" x2="0.381" y2="-0.889" width="0.127" layer="21"/>
<wire x1="0.381" y1="-0.889" x2="0.635" y2="-0.635" width="0.127" layer="21"/>
<wire x1="0.635" y1="-0.635" x2="0.889" y2="-0.889" width="0.127" layer="21"/>
<wire x1="0.889" y1="-0.889" x2="1.651" y2="-0.889" width="0.127" layer="21"/>
<wire x1="1.651" y1="-0.889" x2="1.905" y2="-0.635" width="0.127" layer="21"/>
<wire x1="1.905" y1="-0.635" x2="2.159" y2="-0.889" width="0.127" layer="21"/>
<wire x1="2.159" y1="-0.889" x2="2.921" y2="-0.889" width="0.127" layer="21"/>
<wire x1="2.921" y1="-0.889" x2="3.175" y2="-0.635" width="0.127" layer="21"/>
<wire x1="3.175" y1="-0.635" x2="3.429" y2="-0.889" width="0.127" layer="21"/>
<wire x1="3.429" y1="-0.889" x2="4.191" y2="-0.889" width="0.127" layer="21"/>
<wire x1="4.191" y1="0.889" x2="3.429" y2="0.889" width="0.127" layer="21"/>
<wire x1="3.429" y1="0.889" x2="3.175" y2="0.635" width="0.127" layer="21"/>
<wire x1="3.175" y1="0.635" x2="2.921" y2="0.889" width="0.127" layer="21"/>
<wire x1="2.921" y1="0.889" x2="2.159" y2="0.889" width="0.127" layer="21"/>
<wire x1="2.159" y1="0.889" x2="1.905" y2="0.635" width="0.127" layer="21"/>
<wire x1="1.905" y1="0.635" x2="1.651" y2="0.889" width="0.127" layer="21"/>
<wire x1="1.651" y1="0.889" x2="0.889" y2="0.889" width="0.127" layer="21"/>
<wire x1="0.889" y1="0.889" x2="0.635" y2="0.635" width="0.127" layer="21"/>
<wire x1="0.635" y1="0.635" x2="0.381" y2="0.889" width="0.127" layer="21"/>
<wire x1="0.381" y1="0.889" x2="-0.381" y2="0.889" width="0.127" layer="21"/>
<wire x1="-0.381" y1="0.889" x2="-0.889" y2="0.381" width="0.127" layer="21"/>
<wire x1="-0.889" y1="-0.381" x2="-0.381" y2="-0.889" width="0.127" layer="21"/>
<wire x1="-0.889" y1="0.381" x2="-0.889" y2="-0.381" width="0.127" layer="21"/>
<wire x1="4.191" y1="0.889" x2="4.699" y2="0.381" width="0.127" layer="21"/>
<wire x1="4.699" y1="0.381" x2="4.699" y2="-0.381" width="0.127" layer="21"/>
<wire x1="4.699" y1="-0.381" x2="4.191" y2="-0.889" width="0.127" layer="21"/>
<pad name="4" x="3.81" y="0" drill="0.508" diameter="1"/>
<pad name="3" x="2.54" y="0" drill="0.508" diameter="1"/>
<pad name="2" x="1.27" y="0" drill="0.508" diameter="1"/>
<pad name="1" x="0" y="0" drill="0.508" diameter="1"/>
<text x="-0.508" y="1.27" size="0.4064" layer="25">&gt;NAME</text>
<text x="-0.508" y="-1.651" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="1X04_LOCK">
<wire x1="6.985" y1="1.27" x2="8.255" y2="1.27" width="0.2032" layer="21"/>
<wire x1="8.255" y1="1.27" x2="8.89" y2="0.635" width="0.2032" layer="21"/>
<wire x1="8.89" y1="-0.635" x2="8.255" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="3.81" y1="0.635" x2="4.445" y2="1.27" width="0.2032" layer="21"/>
<wire x1="4.445" y1="1.27" x2="5.715" y2="1.27" width="0.2032" layer="21"/>
<wire x1="5.715" y1="1.27" x2="6.35" y2="0.635" width="0.2032" layer="21"/>
<wire x1="6.35" y1="-0.635" x2="5.715" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="5.715" y1="-1.27" x2="4.445" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="4.445" y1="-1.27" x2="3.81" y2="-0.635" width="0.2032" layer="21"/>
<wire x1="6.985" y1="1.27" x2="6.35" y2="0.635" width="0.2032" layer="21"/>
<wire x1="6.35" y1="-0.635" x2="6.985" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="8.255" y1="-1.27" x2="6.985" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="-0.635" y1="1.27" x2="0.635" y2="1.27" width="0.2032" layer="21"/>
<wire x1="0.635" y1="1.27" x2="1.27" y2="0.635" width="0.2032" layer="21"/>
<wire x1="1.27" y1="-0.635" x2="0.635" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="1.27" y1="0.635" x2="1.905" y2="1.27" width="0.2032" layer="21"/>
<wire x1="1.905" y1="1.27" x2="3.175" y2="1.27" width="0.2032" layer="21"/>
<wire x1="3.175" y1="1.27" x2="3.81" y2="0.635" width="0.2032" layer="21"/>
<wire x1="3.81" y1="-0.635" x2="3.175" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="3.175" y1="-1.27" x2="1.905" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="1.905" y1="-1.27" x2="1.27" y2="-0.635" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="0.635" x2="-1.27" y2="-0.635" width="0.2032" layer="21"/>
<wire x1="-0.635" y1="1.27" x2="-1.27" y2="0.635" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="-0.635" x2="-0.635" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="0.635" y1="-1.27" x2="-0.635" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="8.89" y1="0.635" x2="8.89" y2="-0.635" width="0.2032" layer="21"/>
<pad name="1" x="0" y="0.127" drill="1.016" diameter="1.8796" shape="square" rot="R90"/>
<pad name="2" x="2.54" y="-0.127" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="3" x="5.08" y="0.127" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="4" x="7.62" y="-0.127" drill="1.016" diameter="1.8796" rot="R90"/>
<text x="-1.3462" y="1.8288" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-1.27" y="-3.175" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="7.366" y1="-0.254" x2="7.874" y2="0.254" layer="51"/>
<rectangle x1="4.826" y1="-0.254" x2="5.334" y2="0.254" layer="51"/>
<rectangle x1="2.286" y1="-0.254" x2="2.794" y2="0.254" layer="51"/>
<rectangle x1="-0.254" y1="-0.254" x2="0.254" y2="0.254" layer="51"/>
</package>
<package name="1X04_LOCK_LONGPADS">
<description>This footprint was designed to help hold the alignment of a through-hole component (i.e.  6-pin header) while soldering it into place.  
You may notice that each hole has been shifted either up or down by 0.005 of an inch from it's more standard position (which is a perfectly straight line).  
This slight alteration caused the pins (the squares in the middle) to touch the edges of the holes.  Because they are alternating, it causes a "brace" 
to hold the component in place.  0.005 has proven to be the perfect amount of "off-center" position when using our standard breakaway headers.
Although looks a little odd when you look at the bare footprint, once you have a header in there, the alteration is very hard to notice.  Also,
if you push a header all the way into place, it is covered up entirely on the bottom side.  This idea of altering the position of holes to aid alignment 
will be further integrated into the Sparkfun Library for other footprints.  It can help hold any component with 3 or more connection pins.</description>
<wire x1="1.524" y1="-0.127" x2="1.016" y2="-0.127" width="0.2032" layer="21"/>
<wire x1="4.064" y1="-0.127" x2="3.556" y2="-0.127" width="0.2032" layer="21"/>
<wire x1="6.604" y1="-0.127" x2="6.096" y2="-0.127" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="-0.127" x2="-1.016" y2="-0.127" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="-0.127" x2="-1.27" y2="0.8636" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="0.8636" x2="-0.9906" y2="1.143" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="-0.127" x2="-1.27" y2="-1.1176" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="-1.1176" x2="-0.9906" y2="-1.397" width="0.2032" layer="21"/>
<wire x1="8.89" y1="-0.127" x2="8.636" y2="-0.127" width="0.2032" layer="21"/>
<wire x1="8.89" y1="-0.127" x2="8.89" y2="-1.1176" width="0.2032" layer="21"/>
<wire x1="8.89" y1="-1.1176" x2="8.6106" y2="-1.397" width="0.2032" layer="21"/>
<wire x1="8.89" y1="-0.127" x2="8.89" y2="0.8636" width="0.2032" layer="21"/>
<wire x1="8.89" y1="0.8636" x2="8.6106" y2="1.143" width="0.2032" layer="21"/>
<pad name="1" x="0" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="2" x="2.54" y="-0.254" drill="1.016" shape="long" rot="R90"/>
<pad name="3" x="5.08" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="4" x="7.62" y="-0.254" drill="1.016" shape="long" rot="R90"/>
<text x="-1.27" y="1.778" size="1.27" layer="25" font="vector">&gt;NAME</text>
<text x="-1.27" y="-3.302" size="1.27" layer="27" font="vector">&gt;VALUE</text>
<rectangle x1="-0.2921" y1="-0.4191" x2="0.2921" y2="0.1651" layer="51"/>
<rectangle x1="2.2479" y1="-0.4191" x2="2.8321" y2="0.1651" layer="51"/>
<rectangle x1="4.7879" y1="-0.4191" x2="5.3721" y2="0.1651" layer="51"/>
<rectangle x1="7.3279" y1="-0.4191" x2="7.9121" y2="0.1651" layer="51" rot="R90"/>
</package>
<package name="MOLEX-1X4_LOCK">
<wire x1="-1.27" y1="3.048" x2="-1.27" y2="-2.54" width="0.127" layer="21"/>
<wire x1="8.89" y1="3.048" x2="8.89" y2="-2.54" width="0.127" layer="21"/>
<wire x1="8.89" y1="3.048" x2="-1.27" y2="3.048" width="0.127" layer="21"/>
<wire x1="8.89" y1="-2.54" x2="7.62" y2="-2.54" width="0.127" layer="21"/>
<wire x1="7.62" y1="-2.54" x2="0" y2="-2.54" width="0.127" layer="21"/>
<wire x1="0" y1="-2.54" x2="-1.27" y2="-2.54" width="0.127" layer="21"/>
<wire x1="0" y1="-2.54" x2="0" y2="-1.27" width="0.127" layer="21"/>
<wire x1="0" y1="-1.27" x2="7.62" y2="-1.27" width="0.127" layer="21"/>
<wire x1="7.62" y1="-1.27" x2="7.62" y2="-2.54" width="0.127" layer="21"/>
<pad name="1" x="0" y="0.127" drill="1.016" diameter="1.8796" shape="square"/>
<pad name="2" x="2.54" y="-0.127" drill="1.016" diameter="1.8796"/>
<pad name="3" x="5.08" y="0.127" drill="1.016" diameter="1.8796"/>
<pad name="4" x="7.62" y="-0.127" drill="1.016" diameter="1.8796"/>
</package>
<package name="1X04-SMD">
<wire x1="5.08" y1="1.25" x2="-5.08" y2="1.25" width="0.127" layer="51"/>
<wire x1="-5.08" y1="1.25" x2="-5.08" y2="-1.25" width="0.127" layer="51"/>
<wire x1="-5.08" y1="-1.25" x2="-3.81" y2="-1.25" width="0.127" layer="51"/>
<wire x1="-3.81" y1="-1.25" x2="-1.27" y2="-1.25" width="0.127" layer="51"/>
<wire x1="-1.27" y1="-1.25" x2="1.27" y2="-1.25" width="0.127" layer="51"/>
<wire x1="1.27" y1="-1.25" x2="3.81" y2="-1.25" width="0.127" layer="51"/>
<wire x1="3.81" y1="-1.25" x2="5.08" y2="-1.25" width="0.127" layer="51"/>
<wire x1="5.08" y1="-1.25" x2="5.08" y2="1.25" width="0.127" layer="51"/>
<wire x1="3.81" y1="-1.25" x2="3.81" y2="-7.25" width="0.127" layer="51"/>
<wire x1="1.27" y1="-1.25" x2="1.27" y2="-7.25" width="0.127" layer="51"/>
<wire x1="-1.27" y1="-1.25" x2="-1.27" y2="-7.25" width="0.127" layer="51"/>
<wire x1="-3.81" y1="-1.25" x2="-3.81" y2="-7.25" width="0.127" layer="51"/>
<smd name="4" x="3.81" y="5" dx="3" dy="1" layer="1" rot="R90"/>
<smd name="3" x="1.27" y="5" dx="3" dy="1" layer="1" rot="R90"/>
<smd name="2" x="-1.27" y="5" dx="3" dy="1" layer="1" rot="R90"/>
<smd name="1" x="-3.81" y="5" dx="3" dy="1" layer="1" rot="R90"/>
<hole x="-2.54" y="0" drill="1.4"/>
<hole x="2.54" y="0" drill="1.4"/>
</package>
<package name="1X04_LONGPADS">
<wire x1="-1.27" y1="0.635" x2="-1.27" y2="-0.635" width="0.2032" layer="21"/>
<wire x1="8.89" y1="0.635" x2="8.89" y2="-0.635" width="0.2032" layer="21"/>
<pad name="1" x="0" y="0" drill="1.1176" diameter="1.8796" shape="long" rot="R90"/>
<pad name="2" x="2.54" y="0" drill="1.1176" diameter="1.8796" shape="long" rot="R90"/>
<pad name="3" x="5.08" y="0" drill="1.1176" diameter="1.8796" shape="long" rot="R90"/>
<pad name="4" x="7.62" y="0" drill="1.1176" diameter="1.8796" shape="long" rot="R90"/>
<text x="-1.3462" y="2.4638" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-1.27" y="-3.81" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="7.366" y1="-0.254" x2="7.874" y2="0.254" layer="51"/>
<rectangle x1="4.826" y1="-0.254" x2="5.334" y2="0.254" layer="51"/>
<rectangle x1="2.286" y1="-0.254" x2="2.794" y2="0.254" layer="51"/>
<rectangle x1="-0.254" y1="-0.254" x2="0.254" y2="0.254" layer="51"/>
</package>
<package name="1X04_NO_SILK">
<pad name="1" x="0" y="0" drill="1.016" diameter="1.8796" shape="square" rot="R90"/>
<pad name="2" x="2.54" y="0" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="3" x="5.08" y="0" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="4" x="7.62" y="0" drill="1.016" diameter="1.8796" rot="R90"/>
<text x="-1.3462" y="1.8288" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-1.27" y="-3.175" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="7.366" y1="-0.254" x2="7.874" y2="0.254" layer="51"/>
<rectangle x1="4.826" y1="-0.254" x2="5.334" y2="0.254" layer="51"/>
<rectangle x1="2.286" y1="-0.254" x2="2.794" y2="0.254" layer="51"/>
<rectangle x1="-0.254" y1="-0.254" x2="0.254" y2="0.254" layer="51"/>
</package>
<package name="JST-4-PTH">
<pad name="1" x="-3" y="0" drill="0.7" diameter="1.6"/>
<pad name="2" x="-1" y="0" drill="0.7" diameter="1.6"/>
<pad name="3" x="1" y="0" drill="0.7" diameter="1.6"/>
<pad name="4" x="3" y="0" drill="0.7" diameter="1.6"/>
<text x="-2.27" y="5.27" size="0.4064" layer="25">&gt;Name</text>
<text x="-2.27" y="4" size="0.4064" layer="27">&gt;Value</text>
<text x="-3.4" y="0.7" size="1.27" layer="51">+</text>
<text x="-1.4" y="0.7" size="1.27" layer="51">-</text>
<text x="0.7" y="0.9" size="0.8" layer="51">S</text>
<text x="2.7" y="0.9" size="0.8" layer="51">S</text>
<wire x1="-4.95" y1="-1.6" x2="-4.95" y2="6" width="0.2032" layer="21"/>
<wire x1="-4.95" y1="6" x2="4.95" y2="6" width="0.2032" layer="21"/>
<wire x1="4.95" y1="6" x2="4.95" y2="-1.6" width="0.2032" layer="21"/>
<wire x1="-4.95" y1="-1.6" x2="-4.3" y2="-1.6" width="0.2032" layer="21"/>
<wire x1="4.95" y1="-1.6" x2="4.3" y2="-1.6" width="0.2032" layer="21"/>
<wire x1="-4.3" y1="-1.6" x2="-4.3" y2="0" width="0.2032" layer="21"/>
<wire x1="4.3" y1="-1.6" x2="4.3" y2="0" width="0.2032" layer="21"/>
</package>
<package name="SCREWTERMINAL-3.5MM-4_LOCK">
<wire x1="-2.3" y1="3.4" x2="12.8" y2="3.4" width="0.2032" layer="21"/>
<wire x1="12.8" y1="3.4" x2="12.8" y2="-2.8" width="0.2032" layer="21"/>
<wire x1="12.8" y1="-2.8" x2="12.8" y2="-3.6" width="0.2032" layer="21"/>
<wire x1="12.8" y1="-3.6" x2="-2.3" y2="-3.6" width="0.2032" layer="21"/>
<wire x1="-2.3" y1="-3.6" x2="-2.3" y2="-2.8" width="0.2032" layer="21"/>
<wire x1="-2.3" y1="-2.8" x2="-2.3" y2="3.4" width="0.2032" layer="21"/>
<wire x1="12.8" y1="-2.8" x2="-2.3" y2="-2.8" width="0.2032" layer="21"/>
<wire x1="-2.3" y1="-1.35" x2="-2.7" y2="-1.35" width="0.2032" layer="51"/>
<wire x1="-2.7" y1="-1.35" x2="-2.7" y2="-2.35" width="0.2032" layer="51"/>
<wire x1="-2.7" y1="-2.35" x2="-2.3" y2="-2.35" width="0.2032" layer="51"/>
<wire x1="12.8" y1="3.15" x2="13.2" y2="3.15" width="0.2032" layer="51"/>
<wire x1="13.2" y1="3.15" x2="13.2" y2="2.15" width="0.2032" layer="51"/>
<wire x1="13.2" y1="2.15" x2="12.8" y2="2.15" width="0.2032" layer="51"/>
<circle x="0" y="0" radius="0.425" width="0.001" layer="51"/>
<circle x="3.5" y="0" radius="0.425" width="0.001" layer="51"/>
<circle x="7" y="0" radius="0.425" width="0.001" layer="51"/>
<circle x="10.5" y="0" radius="0.425" width="0.001" layer="51"/>
<pad name="1" x="-0.1778" y="0" drill="1.2" diameter="2.032" shape="square"/>
<pad name="2" x="3.6778" y="0" drill="1.2" diameter="2.032"/>
<pad name="3" x="6.8222" y="0" drill="1.2" diameter="2.032"/>
<pad name="4" x="10.6778" y="0" drill="1.2" diameter="2.032"/>
<text x="-1.27" y="2.54" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.27" y="1.27" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="1X04-1MM-RA">
<wire x1="-1.5" y1="-4.6" x2="1.5" y2="-4.6" width="0.254" layer="21"/>
<wire x1="-3" y1="-2" x2="-3" y2="-0.35" width="0.254" layer="21"/>
<wire x1="2.25" y1="-0.35" x2="3" y2="-0.35" width="0.254" layer="21"/>
<wire x1="3" y1="-0.35" x2="3" y2="-2" width="0.254" layer="21"/>
<wire x1="-3" y1="-0.35" x2="-2.25" y2="-0.35" width="0.254" layer="21"/>
<circle x="-2.5" y="0.3" radius="0.1414" width="0.4" layer="21"/>
<smd name="NC2" x="-2.8" y="-3.675" dx="1.2" dy="2" layer="1"/>
<smd name="NC1" x="2.8" y="-3.675" dx="1.2" dy="2" layer="1"/>
<smd name="1" x="-1.5" y="0" dx="0.6" dy="1.35" layer="1"/>
<smd name="2" x="-0.5" y="0" dx="0.6" dy="1.35" layer="1"/>
<smd name="3" x="0.5" y="0" dx="0.6" dy="1.35" layer="1"/>
<smd name="4" x="1.5" y="0" dx="0.6" dy="1.35" layer="1"/>
<text x="-1.73" y="1.73" size="0.4064" layer="25" rot="R180">&gt;NAME</text>
<text x="3.46" y="1.73" size="0.4064" layer="27" rot="R180">&gt;VALUE</text>
</package>
<package name="1X04_SMD_STRAIGHT_COMBO">
<wire x1="7.62" y1="1.27" x2="7.62" y2="-1.27" width="0.4064" layer="1"/>
<wire x1="5.08" y1="1.27" x2="5.08" y2="-1.27" width="0.4064" layer="1"/>
<wire x1="2.54" y1="1.27" x2="2.54" y2="-1.27" width="0.4064" layer="1"/>
<wire x1="0" y1="1.27" x2="0" y2="-1.27" width="0.4064" layer="1"/>
<wire x1="-1.37" y1="-1.25" x2="-1.37" y2="1.25" width="0.1778" layer="21"/>
<wire x1="8.99" y1="1.25" x2="8.99" y2="-1.25" width="0.1778" layer="21"/>
<wire x1="-0.73" y1="-1.25" x2="-1.37" y2="-1.25" width="0.1778" layer="21"/>
<wire x1="8.99" y1="-1.25" x2="8.32" y2="-1.25" width="0.1778" layer="21"/>
<wire x1="8.32" y1="1.25" x2="8.99" y2="1.25" width="0.1778" layer="21"/>
<wire x1="-1.37" y1="1.25" x2="-0.73" y2="1.25" width="0.1778" layer="21"/>
<wire x1="5.869" y1="-1.29" x2="6.831" y2="-1.29" width="0.1778" layer="21"/>
<wire x1="5.869" y1="1.25" x2="6.831" y2="1.25" width="0.1778" layer="21"/>
<wire x1="3.329" y1="-1.29" x2="4.291" y2="-1.29" width="0.1778" layer="21"/>
<wire x1="3.329" y1="1.25" x2="4.291" y2="1.25" width="0.1778" layer="21"/>
<wire x1="0.789" y1="-1.29" x2="1.751" y2="-1.29" width="0.1778" layer="21"/>
<wire x1="0.789" y1="1.25" x2="1.751" y2="1.25" width="0.1778" layer="21"/>
<smd name="3" x="5.08" y="-1.65" dx="2" dy="1" layer="1" rot="R270"/>
<smd name="1" x="0" y="-1.65" dx="2" dy="1" layer="1" rot="R270"/>
<smd name="4" x="7.62" y="1.65" dx="2" dy="1" layer="1" rot="R270"/>
<smd name="2" x="2.54" y="1.65" dx="2" dy="1" layer="1" rot="R270"/>
<smd name="1-2" x="0" y="1.65" dx="2" dy="1" layer="1" rot="R90"/>
<smd name="2-2" x="2.54" y="-1.65" dx="2" dy="1" layer="1" rot="R90"/>
<smd name="3-2" x="5.08" y="1.65" dx="2" dy="1" layer="1" rot="R90"/>
<smd name="4-2" x="7.62" y="-1.65" dx="2" dy="1" layer="1" rot="R90"/>
<text x="0" y="2.921" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="0" y="-4.191" size="1.27" layer="27">&gt;VALUE</text>
</package>
<package name="1X04-SMD_LONG">
<wire x1="5.08" y1="1.25" x2="-5.08" y2="1.25" width="0.127" layer="51"/>
<wire x1="-5.08" y1="1.25" x2="-5.08" y2="-1.25" width="0.127" layer="51"/>
<wire x1="-5.08" y1="-1.25" x2="-3.81" y2="-1.25" width="0.127" layer="51"/>
<wire x1="-3.81" y1="-1.25" x2="-1.27" y2="-1.25" width="0.127" layer="51"/>
<wire x1="-1.27" y1="-1.25" x2="1.27" y2="-1.25" width="0.127" layer="51"/>
<wire x1="1.27" y1="-1.25" x2="3.81" y2="-1.25" width="0.127" layer="51"/>
<wire x1="3.81" y1="-1.25" x2="5.08" y2="-1.25" width="0.127" layer="51"/>
<wire x1="5.08" y1="-1.25" x2="5.08" y2="1.25" width="0.127" layer="51"/>
<wire x1="3.81" y1="-1.25" x2="3.81" y2="-7.25" width="0.127" layer="51"/>
<wire x1="1.27" y1="-1.25" x2="1.27" y2="-7.25" width="0.127" layer="51"/>
<wire x1="-1.27" y1="-1.25" x2="-1.27" y2="-7.25" width="0.127" layer="51"/>
<wire x1="-3.81" y1="-1.25" x2="-3.81" y2="-7.25" width="0.127" layer="51"/>
<smd name="4" x="3.81" y="5.5" dx="4" dy="1" layer="1" rot="R90"/>
<smd name="3" x="1.27" y="5.5" dx="4" dy="1" layer="1" rot="R90"/>
<smd name="2" x="-1.27" y="5.5" dx="4" dy="1" layer="1" rot="R90"/>
<smd name="1" x="-3.81" y="5.5" dx="4" dy="1" layer="1" rot="R90"/>
<hole x="-2.54" y="0" drill="1.4"/>
<hole x="2.54" y="0" drill="1.4"/>
</package>
<package name="JST-4-PTH-VERT">
<wire x1="-4.95" y1="-2.25" x2="-4.95" y2="2.25" width="0.2032" layer="21"/>
<wire x1="-4.95" y1="2.25" x2="4.95" y2="2.25" width="0.2032" layer="21"/>
<wire x1="4.95" y1="-2.25" x2="1" y2="-2.25" width="0.2032" layer="21"/>
<wire x1="-1" y1="-2.25" x2="-4.95" y2="-2.25" width="0.2032" layer="21"/>
<wire x1="-1" y1="-1.75" x2="1" y2="-1.75" width="0.2032" layer="21"/>
<wire x1="1" y1="-1.75" x2="1" y2="-2.25" width="0.2032" layer="21"/>
<wire x1="-1" y1="-1.75" x2="-1" y2="-2.25" width="0.2032" layer="21"/>
<wire x1="4.95" y1="2.25" x2="4.95" y2="-2.25" width="0.2032" layer="21"/>
<pad name="1" x="-3" y="-0.55" drill="0.7" diameter="1.6"/>
<pad name="2" x="-1" y="-0.55" drill="0.7" diameter="1.6"/>
<pad name="3" x="1" y="-0.55" drill="0.7" diameter="1.6"/>
<pad name="4" x="3" y="-0.55" drill="0.7" diameter="1.6"/>
<text x="-3" y="3" size="0.4064" layer="25">&gt;Name</text>
<text x="1" y="3" size="0.4064" layer="27">&gt;Value</text>
<text x="-1.4" y="0.75" size="1.27" layer="51">+</text>
<text x="0.6" y="0.75" size="1.27" layer="51">-</text>
<text x="2.7" y="0.95" size="0.8" layer="51">Y</text>
<text x="-3.3" y="0.95" size="0.8" layer="51">B</text>
</package>
<package name="1X04_SMD_RA_FEMALE">
<wire x1="-5.205" y1="4.25" x2="-5.205" y2="-4.25" width="0.1778" layer="21"/>
<wire x1="5.205" y1="4.25" x2="-5.205" y2="4.25" width="0.1778" layer="21"/>
<wire x1="5.205" y1="-4.25" x2="5.205" y2="4.25" width="0.1778" layer="21"/>
<wire x1="-5.205" y1="-4.25" x2="5.205" y2="-4.25" width="0.1778" layer="21"/>
<rectangle x1="-1.59" y1="6.8" x2="-0.95" y2="7.65" layer="51"/>
<rectangle x1="0.95" y1="6.8" x2="1.59" y2="7.65" layer="51"/>
<rectangle x1="-4.13" y1="6.8" x2="-3.49" y2="7.65" layer="51"/>
<smd name="3" x="1.27" y="7.225" dx="1.25" dy="3" layer="1" rot="R180"/>
<smd name="2" x="-1.27" y="7.225" dx="1.25" dy="3" layer="1" rot="R180"/>
<smd name="1" x="-3.81" y="7.225" dx="1.25" dy="3" layer="1" rot="R180"/>
<text x="-4.425" y="2.775" size="1" layer="27">&gt;Value</text>
<text x="-4.225" y="-3.395" size="1" layer="25">&gt;Name</text>
<rectangle x1="3.49" y1="6.8" x2="4.13" y2="7.65" layer="51"/>
<smd name="4" x="3.81" y="7.225" dx="1.25" dy="3" layer="1" rot="R180"/>
</package>
<package name="1X04-1.5MM_JST">
<pad name="4" x="4.5" y="0" drill="0.7"/>
<pad name="3" x="3" y="0" drill="0.7"/>
<pad name="2" x="1.5" y="0" drill="0.7"/>
<pad name="1" x="0" y="0" drill="0.7"/>
<text x="-0.508" y="1.27" size="0.4064" layer="25">&gt;NAME</text>
<text x="-0.508" y="-1.651" size="0.4064" layer="27">&gt;VALUE</text>
<wire x1="-1.5" y1="2.2" x2="6" y2="2.2" width="0.3048" layer="21"/>
<wire x1="6" y1="2.2" x2="6" y2="-1.5" width="0.3048" layer="21"/>
<wire x1="6" y1="-1.5" x2="4.5" y2="-1.5" width="0.3048" layer="21"/>
<wire x1="4.5" y1="-1.5" x2="4.5" y2="-1" width="0.3048" layer="21"/>
<wire x1="4.5" y1="-1" x2="0" y2="-1" width="0.3048" layer="21"/>
<wire x1="0" y1="-1" x2="0" y2="-1.5" width="0.3048" layer="21"/>
<wire x1="0" y1="-1.5" x2="-1.5" y2="-1.5" width="0.3048" layer="21"/>
<wire x1="-1.5" y1="-1.5" x2="-1.5" y2="2.2" width="0.3048" layer="21"/>
</package>
<package name="1X04_NO_SILK_ALL_ROUND">
<pad name="1" x="0" y="0" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="2" x="2.54" y="0" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="3" x="5.08" y="0" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="4" x="7.62" y="0" drill="1.016" diameter="1.8796" rot="R90"/>
<text x="-1.3462" y="1.8288" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-1.27" y="-3.175" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="7.366" y1="-0.254" x2="7.874" y2="0.254" layer="51"/>
<rectangle x1="4.826" y1="-0.254" x2="5.334" y2="0.254" layer="51"/>
<rectangle x1="2.286" y1="-0.254" x2="2.794" y2="0.254" layer="51"/>
<rectangle x1="-0.254" y1="-0.254" x2="0.254" y2="0.254" layer="51"/>
</package>
</packages>
<symbols>
<symbol name="M04">
<wire x1="1.27" y1="-5.08" x2="-5.08" y2="-5.08" width="0.4064" layer="94"/>
<wire x1="-1.27" y1="2.54" x2="0" y2="2.54" width="0.6096" layer="94"/>
<wire x1="-1.27" y1="0" x2="0" y2="0" width="0.6096" layer="94"/>
<wire x1="-1.27" y1="-2.54" x2="0" y2="-2.54" width="0.6096" layer="94"/>
<wire x1="-5.08" y1="7.62" x2="-5.08" y2="-5.08" width="0.4064" layer="94"/>
<wire x1="1.27" y1="-5.08" x2="1.27" y2="7.62" width="0.4064" layer="94"/>
<wire x1="-5.08" y1="7.62" x2="1.27" y2="7.62" width="0.4064" layer="94"/>
<wire x1="-1.27" y1="5.08" x2="0" y2="5.08" width="0.6096" layer="94"/>
<text x="-5.08" y="-7.62" size="1.778" layer="96">&gt;VALUE</text>
<text x="-5.08" y="8.382" size="1.778" layer="95">&gt;NAME</text>
<pin name="1" x="5.08" y="-2.54" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="2" x="5.08" y="0" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="3" x="5.08" y="2.54" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="4" x="5.08" y="5.08" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="M04" prefix="J" uservalue="yes">
<description>&lt;b&gt;Header 4&lt;/b&gt;
Standard 4-pin 0.1" header. Use with straight break away headers (SKU : PRT-00116), right angle break away headers (PRT-00553), swiss pins (PRT-00743), machine pins (PRT-00117), and female headers (PRT-00115). Molex polarized connector foot print use with SKU : PRT-08231 with associated crimp pins and housings. 1MM SMD Version SKU: PRT-10208</description>
<gates>
<gate name="G$1" symbol="M04" x="-2.54" y="0"/>
</gates>
<devices>
<device name="PTH" package="1X04">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
</connects>
<technologies>
<technology name="">
<attribute name="PROD_ID" value="CONN-09696" constant="no"/>
</technology>
</technologies>
</device>
<device name="POLAR" package="MOLEX-1X4">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="SCREW" package="SCREWTERMINAL-3.5MM-4">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
</connects>
<technologies>
<technology name="">
<attribute name="PROD_ID" value="Combine 2x8399" constant="no"/>
</technology>
</technologies>
</device>
<device name="1.27MM" package="1X04-1.27MM">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="LOCK" package="1X04_LOCK">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
</connects>
<technologies>
<technology name="">
<attribute name="PROD_ID" value="CONN-09696" constant="no"/>
</technology>
</technologies>
</device>
<device name="LOCK_LONGPADS" package="1X04_LOCK_LONGPADS">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
</connects>
<technologies>
<technology name="">
<attribute name="PROD_ID" value="CONN-09696" constant="no"/>
</technology>
</technologies>
</device>
<device name="POLAR_LOCK" package="MOLEX-1X4_LOCK">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="SMD" package="1X04-SMD">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="LONGPADS" package="1X04_LONGPADS">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
</connects>
<technologies>
<technology name="">
<attribute name="PROD_ID" value="CONN-09696" constant="no"/>
</technology>
</technologies>
</device>
<device name="1X04_NO_SILK" package="1X04_NO_SILK">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
</connects>
<technologies>
<technology name="">
<attribute name="PROD_ID" value="CONN-09696" constant="no"/>
</technology>
</technologies>
</device>
<device name="JST-PTH" package="JST-4-PTH">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
</connects>
<technologies>
<technology name="">
<attribute name="SKU" value="PRT-09916" constant="no"/>
</technology>
</technologies>
</device>
<device name="SCREW_LOCK" package="SCREWTERMINAL-3.5MM-4_LOCK">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="SMD2" package="1X04-1MM-RA">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="SMD_STRAIGHT_COMBO" package="1X04_SMD_STRAIGHT_COMBO">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
</connects>
<technologies>
<technology name="">
<attribute name="PROD_ID" value="CONN-08511"/>
<attribute name="VALUE" value="1X04_SMD_STRAIGHT_COMBO"/>
</technology>
</technologies>
</device>
<device name="SMD_LONG" package="1X04-SMD_LONG">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="JST-PTH-VERT" package="JST-4-PTH-VERT">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="SMD_RA_FEMALE" package="1X04_SMD_RA_FEMALE">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="JST" package="1X04-1.5MM_JST">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
</connects>
<technologies>
<technology name="">
<attribute name="PROD_ID" value="CONN-12477"/>
</technology>
</technologies>
</device>
<device name="NO_SILK_ALL_ROUND" package="1X04_NO_SILK_ALL_ROUND">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
</connects>
<technologies>
<technology name="">
<attribute name="PROD_ID" value="CONN-09696" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="IC1" library="cc1101" deviceset="CC1101" device="">
<attribute name="DIGIKEY" value="296-35718-1-ND"/>
<attribute name="MOUSER" value="595-CC1101RGPR"/>
</part>
<part name="U4" library="johanson-baluns" deviceset="0896BM15A0001" device="">
<attribute name="MOUSER" value="609-0433BM15A0001E"/>
</part>
<part name="X1" library="cc1101" deviceset="XTAL" device="-3.2X2.5">
<attribute name="DIGIKEY" value="644-1261-1-ND"/>
</part>
<part name="ANT" library="HF-Bauteile" deviceset="433CHIP" device="">
<attribute name="MOUSER" value="603-ANT1204F002R0433"/>
</part>
<part name="GND7" library="supply1" deviceset="GND" device=""/>
<part name="GND10" library="supply1" deviceset="GND" device=""/>
<part name="GND8" library="supply1" deviceset="GND" device=""/>
<part name="GND15" library="supply1" deviceset="GND" device=""/>
<part name="C9" library="tiny_passives" deviceset="C-EU" device="" value="0.1uF">
<attribute name="MOUSER" value="581-530L104KT16T"/>
</part>
<part name="C10" library="tiny_passives" deviceset="C-EU" device="" value="0.01uF">
<attribute name="MOUSER" value="80-C0402T103K5RCL"/>
</part>
<part name="C11" library="tiny_passives" deviceset="C-EU" device="" value="12pF">
<attribute name="MOUSER" value="581-04025U120FAT2A"/>
</part>
<part name="C12" library="tiny_passives" deviceset="C-EU" device="" value="15pf">
<attribute name="MOUSER" value="80-CBR04C150F1GAC"/>
</part>
<part name="R7" library="tiny_passives" deviceset="R-EU" device="" value="56k">
<attribute name="DIGIKEY" value="311-56KJRCT-ND"/>
<attribute name="MOUSER" value="603-RC0402JR-0756KL"/>
</part>
<part name="GND1" library="supply1" deviceset="GND" device=""/>
<part name="GND2" library="supply1" deviceset="GND" device=""/>
<part name="C1" library="tiny_passives" deviceset="C-EU" device="" value="0.1uF">
<attribute name="MOUSER" value="581-530L104KT16T"/>
</part>
<part name="C2" library="tiny_passives" deviceset="C-EU" device="" value="220pF">
<attribute name="MOUSER" value="605-500X07W221MV4T"/>
</part>
<part name="GND3" library="supply1" deviceset="GND" device=""/>
<part name="GND4" library="supply1" deviceset="GND" device=""/>
<part name="C3" library="tiny_passives" deviceset="C-EU" device="" value="220pF">
<attribute name="MOUSER" value="605-500X07W221MV4T"/>
</part>
<part name="C4" library="tiny_passives" deviceset="C-EU" device="" value="220pF">
<attribute name="MOUSER" value="605-500X07W221MV4T"/>
</part>
<part name="C5" library="tiny_passives" deviceset="C-EU" device="" value="0.01uF">
<attribute name="MOUSER" value="80-C0402T103K5RCL"/>
</part>
<part name="GND5" library="supply1" deviceset="GND" device=""/>
<part name="GND6" library="supply1" deviceset="GND" device=""/>
<part name="GND9" library="supply1" deviceset="GND" device=""/>
<part name="GND11" library="supply1" deviceset="GND" device=""/>
<part name="J2" library="SparkFun-Connectors" deviceset="M04" device="PTH"/>
<part name="J1" library="SparkFun-Connectors" deviceset="M04" device="PTH"/>
</parts>
<sheets>
<sheet>
<plain>
<text x="187.96" y="-40.64" size="1.778" layer="91">433MHz
ANT1204F002R0433A</text>
<text x="91.44" y="-5.08" size="5.08" layer="91">CC1101 Radio</text>
</plain>
<instances>
<instance part="IC1" gate="G$1" x="88.9" y="-43.18">
<attribute name="DIGIKEY" x="88.9" y="-43.18" size="1.778" layer="96" display="off"/>
<attribute name="MOUSER" x="88.9" y="-43.18" size="1.778" layer="96" display="off"/>
</instance>
<instance part="U4" gate="G$1" x="162.56" y="-50.8">
<attribute name="MOUSER" x="162.56" y="-50.8" size="1.778" layer="96" display="off"/>
</instance>
<instance part="X1" gate="G$1" x="129.54" y="-63.5">
<attribute name="DIGIKEY" x="129.54" y="-63.5" size="1.778" layer="96" display="off"/>
</instance>
<instance part="ANT" gate="G$1" x="187.96" y="-45.72">
<attribute name="MOUSER" x="187.96" y="-45.72" size="1.778" layer="96" display="off"/>
</instance>
<instance part="GND7" gate="1" x="58.42" y="-78.74"/>
<instance part="GND10" gate="1" x="137.16" y="-78.74"/>
<instance part="GND8" gate="1" x="121.92" y="-40.64" rot="R90"/>
<instance part="GND15" gate="1" x="149.86" y="-20.32" rot="R90"/>
<instance part="C9" gate="C1" x="33.02" y="-71.12" rot="R180">
<attribute name="MOUSER" x="33.02" y="-71.12" size="1.778" layer="96" rot="R180" display="off"/>
</instance>
<instance part="C10" gate="C1" x="142.24" y="-20.32" rot="R270">
<attribute name="MOUSER" x="142.24" y="-20.32" size="1.778" layer="96" rot="R270" display="off"/>
</instance>
<instance part="C11" gate="C1" x="121.92" y="-71.12" rot="R180">
<attribute name="MOUSER" x="121.92" y="-71.12" size="1.778" layer="96" rot="R180" display="off"/>
</instance>
<instance part="C12" gate="C1" x="137.16" y="-71.12" rot="R180">
<attribute name="MOUSER" x="137.16" y="-71.12" size="1.778" layer="96" rot="R180" display="off"/>
</instance>
<instance part="R7" gate="R1" x="114.3" y="-40.64">
<attribute name="DIGIKEY" x="114.3" y="-40.64" size="1.778" layer="96" display="off"/>
<attribute name="MOUSER" x="114.3" y="-40.64" size="1.778" layer="96" display="off"/>
</instance>
<instance part="GND1" gate="1" x="121.92" y="-78.74"/>
<instance part="GND2" gate="1" x="111.76" y="-78.74"/>
<instance part="C1" gate="C1" x="40.64" y="-53.34" rot="R180">
<attribute name="MOUSER" x="40.64" y="-53.34" size="1.778" layer="96" rot="R180" display="off"/>
</instance>
<instance part="C2" gate="C1" x="58.42" y="-71.12" rot="R180">
<attribute name="MOUSER" x="58.42" y="-71.12" size="1.778" layer="96" rot="R180" display="off"/>
</instance>
<instance part="GND3" gate="1" x="40.64" y="-60.96"/>
<instance part="GND4" gate="1" x="33.02" y="-78.74"/>
<instance part="C3" gate="C1" x="119.38" y="-25.4" rot="R270">
<attribute name="MOUSER" x="119.38" y="-25.4" size="1.778" layer="96" rot="R270" display="off"/>
</instance>
<instance part="C4" gate="C1" x="132.08" y="-35.56" rot="R270">
<attribute name="MOUSER" x="132.08" y="-35.56" size="1.778" layer="96" rot="R270" display="off"/>
</instance>
<instance part="C5" gate="C1" x="149.86" y="-30.48" rot="R270">
<attribute name="MOUSER" x="149.86" y="-30.48" size="1.778" layer="96" rot="R270" display="off"/>
</instance>
<instance part="GND5" gate="1" x="129.54" y="-25.4" rot="R90"/>
<instance part="GND6" gate="1" x="157.48" y="-30.48" rot="R90"/>
<instance part="GND9" gate="1" x="139.7" y="-35.56" rot="R90"/>
<instance part="GND11" gate="1" x="182.88" y="-63.5"/>
<instance part="J2" gate="G$1" x="83.82" y="-101.6"/>
<instance part="J1" gate="G$1" x="83.82" y="-83.82"/>
</instances>
<busses>
</busses>
<nets>
<net name="GND" class="0">
<segment>
<pinref part="GND10" gate="1" pin="GND"/>
<wire x1="137.16" y1="-76.2" x2="137.16" y2="-73.66" width="0.1524" layer="91"/>
<pinref part="C12" gate="C1" pin="1"/>
</segment>
<segment>
<pinref part="GND8" gate="1" pin="GND"/>
<pinref part="R7" gate="R1" pin="2"/>
</segment>
<segment>
<pinref part="C11" gate="C1" pin="1"/>
<wire x1="121.92" y1="-73.66" x2="121.92" y2="-76.2" width="0.1524" layer="91"/>
<pinref part="GND1" gate="1" pin="GND"/>
</segment>
<segment>
<pinref part="GND2" gate="1" pin="GND"/>
<wire x1="111.76" y1="-76.2" x2="111.76" y2="-66.04" width="0.1524" layer="91"/>
<pinref part="IC1" gate="G$1" pin="GND"/>
<wire x1="111.76" y1="-66.04" x2="109.22" y2="-66.04" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND4" gate="1" pin="GND"/>
<pinref part="C9" gate="C1" pin="1"/>
<wire x1="33.02" y1="-76.2" x2="33.02" y2="-73.66" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND3" gate="1" pin="GND"/>
<pinref part="C1" gate="C1" pin="1"/>
<wire x1="40.64" y1="-58.42" x2="40.64" y2="-55.88" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND7" gate="1" pin="GND"/>
<pinref part="C2" gate="C1" pin="1"/>
<wire x1="58.42" y1="-76.2" x2="58.42" y2="-73.66" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND5" gate="1" pin="GND"/>
<pinref part="C3" gate="C1" pin="1"/>
<wire x1="127" y1="-25.4" x2="121.92" y2="-25.4" width="0.1524" layer="91"/>
</segment>
<segment>
<wire x1="182.88" y1="-60.96" x2="182.88" y2="-55.88" width="0.1524" layer="91"/>
<pinref part="U4" gate="G$1" pin="GND"/>
<wire x1="182.88" y1="-55.88" x2="180.34" y2="-55.88" width="0.1524" layer="91"/>
<pinref part="GND11" gate="1" pin="GND"/>
</segment>
<segment>
<pinref part="J2" gate="G$1" pin="4"/>
<wire x1="88.9" y1="-96.52" x2="96.52" y2="-96.52" width="0.1524" layer="91"/>
<label x="88.9" y="-96.52" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="GND15" gate="1" pin="GND"/>
<pinref part="C10" gate="C1" pin="1"/>
<wire x1="147.32" y1="-20.32" x2="144.78" y2="-20.32" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND6" gate="1" pin="GND"/>
<pinref part="C5" gate="C1" pin="1"/>
<wire x1="154.94" y1="-30.48" x2="152.4" y2="-30.48" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND9" gate="1" pin="GND"/>
<pinref part="C4" gate="C1" pin="1"/>
<wire x1="137.16" y1="-35.56" x2="134.62" y2="-35.56" width="0.1524" layer="91"/>
</segment>
</net>
<net name="R_VCC" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="AVDD3"/>
<wire x1="111.76" y1="-30.48" x2="109.22" y2="-30.48" width="0.1524" layer="91"/>
<wire x1="111.76" y1="-12.7" x2="114.3" y2="-12.7" width="0.1524" layer="91"/>
<label x="114.3" y="-12.7" size="1.778" layer="95" xref="yes"/>
<wire x1="109.22" y1="-20.32" x2="111.76" y2="-20.32" width="0.1524" layer="91"/>
<pinref part="IC1" gate="G$1" pin="AVDD1"/>
<wire x1="111.76" y1="-12.7" x2="111.76" y2="-20.32" width="0.1524" layer="91"/>
<junction x="111.76" y="-20.32"/>
<pinref part="IC1" gate="G$1" pin="AVDD2"/>
<pinref part="C3" gate="C1" pin="2"/>
<wire x1="114.3" y1="-25.4" x2="111.76" y2="-25.4" width="0.1524" layer="91"/>
<wire x1="111.76" y1="-25.4" x2="109.22" y2="-25.4" width="0.1524" layer="91"/>
<wire x1="111.76" y1="-20.32" x2="111.76" y2="-25.4" width="0.1524" layer="91"/>
<junction x="111.76" y="-25.4"/>
<wire x1="111.76" y1="-25.4" x2="111.76" y2="-30.48" width="0.1524" layer="91"/>
<junction x="111.76" y="-30.48"/>
<pinref part="IC1" gate="G$1" pin="AVDD4"/>
<wire x1="111.76" y1="-35.56" x2="109.22" y2="-35.56" width="0.1524" layer="91"/>
<wire x1="111.76" y1="-30.48" x2="111.76" y2="-35.56" width="0.1524" layer="91"/>
<pinref part="C10" gate="C1" pin="2"/>
<wire x1="137.16" y1="-20.32" x2="111.76" y2="-20.32" width="0.1524" layer="91"/>
<pinref part="C5" gate="C1" pin="2"/>
<wire x1="144.78" y1="-30.48" x2="111.76" y2="-30.48" width="0.1524" layer="91"/>
<pinref part="C4" gate="C1" pin="2"/>
<wire x1="127" y1="-35.56" x2="111.76" y2="-35.56" width="0.1524" layer="91"/>
<junction x="111.76" y="-35.56"/>
</segment>
<segment>
<pinref part="IC1" gate="G$1" pin="DGUARD"/>
<wire x1="48.26" y1="-55.88" x2="68.58" y2="-55.88" width="0.1524" layer="91"/>
<wire x1="48.26" y1="-55.88" x2="48.26" y2="-66.04" width="0.1524" layer="91"/>
<pinref part="C2" gate="C1" pin="2"/>
<wire x1="58.42" y1="-66.04" x2="48.26" y2="-66.04" width="0.1524" layer="91"/>
<wire x1="22.86" y1="-88.9" x2="35.56" y2="-88.9" width="0.1524" layer="91"/>
<wire x1="35.56" y1="-93.98" x2="30.48" y2="-93.98" width="0.1524" layer="91"/>
<wire x1="35.56" y1="-93.98" x2="35.56" y2="-88.9" width="0.1524" layer="91"/>
<junction x="35.56" y="-88.9"/>
<wire x1="35.56" y1="-88.9" x2="48.26" y2="-88.9" width="0.1524" layer="91"/>
<label x="30.48" y="-93.98" size="1.778" layer="95" rot="R180" xref="yes"/>
<pinref part="C9" gate="C1" pin="2"/>
<wire x1="33.02" y1="-66.04" x2="22.86" y2="-66.04" width="0.1524" layer="91"/>
<pinref part="IC1" gate="G$1" pin="DVDD"/>
<wire x1="68.58" y1="-40.64" x2="22.86" y2="-40.64" width="0.1524" layer="91"/>
<wire x1="22.86" y1="-40.64" x2="22.86" y2="-66.04" width="0.1524" layer="91"/>
<wire x1="22.86" y1="-88.9" x2="22.86" y2="-66.04" width="0.1524" layer="91"/>
<junction x="22.86" y="-66.04"/>
<wire x1="48.26" y1="-88.9" x2="48.26" y2="-66.04" width="0.1524" layer="91"/>
<junction x="48.26" y="-66.04"/>
</segment>
<segment>
<pinref part="J2" gate="G$1" pin="3"/>
<wire x1="88.9" y1="-99.06" x2="96.52" y2="-99.06" width="0.1524" layer="91"/>
<label x="88.9" y="-99.06" size="1.778" layer="95"/>
</segment>
</net>
<net name="SCLK" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="SCLK"/>
<wire x1="68.58" y1="-20.32" x2="63.5" y2="-20.32" width="0.1524" layer="91"/>
<label x="63.5" y="-20.32" size="1.778" layer="95" rot="R180" xref="yes"/>
</segment>
<segment>
<pinref part="J1" gate="G$1" pin="3"/>
<wire x1="88.9" y1="-81.28" x2="96.52" y2="-81.28" width="0.1524" layer="91"/>
<label x="88.9" y="-81.28" size="1.778" layer="95"/>
</segment>
</net>
<net name="MISO" class="0">
<segment>
<wire x1="68.58" y1="-25.4" x2="63.5" y2="-25.4" width="0.1524" layer="91"/>
<label x="63.5" y="-25.4" size="1.778" layer="95" rot="R180" xref="yes"/>
<pinref part="IC1" gate="G$1" pin="SO(GDO1)"/>
</segment>
<segment>
<pinref part="J1" gate="G$1" pin="2"/>
<wire x1="88.9" y1="-83.82" x2="96.52" y2="-83.82" width="0.1524" layer="91"/>
<label x="88.9" y="-83.82" size="1.778" layer="95"/>
</segment>
</net>
<net name="GDO2" class="0">
<segment>
<wire x1="68.58" y1="-30.48" x2="63.5" y2="-30.48" width="0.1524" layer="91"/>
<label x="63.5" y="-30.48" size="1.778" layer="95" rot="R180" xref="yes"/>
<pinref part="IC1" gate="G$1" pin="GDO2"/>
</segment>
<segment>
<pinref part="J1" gate="G$1" pin="1"/>
<wire x1="88.9" y1="-86.36" x2="96.52" y2="-86.36" width="0.1524" layer="91"/>
<label x="88.9" y="-86.36" size="1.778" layer="95"/>
</segment>
</net>
<net name="MOSI" class="0">
<segment>
<wire x1="68.58" y1="-35.56" x2="63.5" y2="-35.56" width="0.1524" layer="91"/>
<label x="63.5" y="-35.56" size="1.778" layer="95" rot="R180" xref="yes"/>
<pinref part="IC1" gate="G$1" pin="SI"/>
</segment>
<segment>
<pinref part="J1" gate="G$1" pin="4"/>
<wire x1="88.9" y1="-78.74" x2="96.52" y2="-78.74" width="0.1524" layer="91"/>
<label x="88.9" y="-78.74" size="1.778" layer="95"/>
</segment>
</net>
<net name="CSN" class="0">
<segment>
<wire x1="68.58" y1="-50.8" x2="63.5" y2="-50.8" width="0.1524" layer="91"/>
<label x="63.5" y="-50.8" size="1.778" layer="95" rot="R180" xref="yes"/>
<pinref part="IC1" gate="G$1" pin="CSN"/>
</segment>
<segment>
<pinref part="J2" gate="G$1" pin="2"/>
<wire x1="88.9" y1="-101.6" x2="96.52" y2="-101.6" width="0.1524" layer="91"/>
<label x="88.9" y="-101.6" size="1.778" layer="95"/>
</segment>
</net>
<net name="GDO0" class="0">
<segment>
<wire x1="68.58" y1="-60.96" x2="63.5" y2="-60.96" width="0.1524" layer="91"/>
<label x="63.5" y="-60.96" size="1.778" layer="95" rot="R180" xref="yes"/>
<pinref part="IC1" gate="G$1" pin="GDO0(ATEST)"/>
</segment>
<segment>
<pinref part="J2" gate="G$1" pin="1"/>
<wire x1="88.9" y1="-104.14" x2="96.52" y2="-104.14" width="0.1524" layer="91"/>
<label x="88.9" y="-104.14" size="1.778" layer="95"/>
</segment>
</net>
<net name="N$1" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="RBIAS"/>
<pinref part="R7" gate="R1" pin="1"/>
</segment>
</net>
<net name="N$7" class="0">
<segment>
<pinref part="X1" gate="G$1" pin="1"/>
<wire x1="127" y1="-63.5" x2="121.92" y2="-63.5" width="0.1524" layer="91"/>
<wire x1="121.92" y1="-63.5" x2="121.92" y2="-66.04" width="0.1524" layer="91"/>
<pinref part="C11" gate="C1" pin="2"/>
<wire x1="121.92" y1="-63.5" x2="121.92" y2="-60.96" width="0.1524" layer="91"/>
<junction x="121.92" y="-63.5"/>
<pinref part="IC1" gate="G$1" pin="XOSC_Q1"/>
<wire x1="121.92" y1="-60.96" x2="109.22" y2="-60.96" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$9" class="0">
<segment>
<pinref part="U4" gate="G$1" pin="UNBAL"/>
<wire x1="180.34" y1="-45.72" x2="182.88" y2="-45.72" width="0.1524" layer="91"/>
<pinref part="ANT" gate="G$1" pin="P$1"/>
</segment>
</net>
<net name="N$2" class="0">
<segment>
<pinref part="C12" gate="C1" pin="2"/>
<wire x1="137.16" y1="-66.04" x2="137.16" y2="-63.5" width="0.1524" layer="91"/>
<pinref part="X1" gate="G$1" pin="2"/>
<wire x1="137.16" y1="-63.5" x2="132.08" y2="-63.5" width="0.1524" layer="91"/>
<wire x1="137.16" y1="-63.5" x2="137.16" y2="-55.88" width="0.1524" layer="91"/>
<junction x="137.16" y="-63.5"/>
<pinref part="IC1" gate="G$1" pin="XOSC_Q2"/>
<wire x1="137.16" y1="-55.88" x2="109.22" y2="-55.88" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$4" class="0">
<segment>
<pinref part="C1" gate="C1" pin="2"/>
<wire x1="40.64" y1="-48.26" x2="40.64" y2="-45.72" width="0.1524" layer="91"/>
<pinref part="IC1" gate="G$1" pin="DCOUPL"/>
<wire x1="40.64" y1="-45.72" x2="68.58" y2="-45.72" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$3" class="0">
<segment>
<pinref part="U4" gate="G$1" pin="BAL4"/>
<wire x1="144.78" y1="-55.88" x2="144.78" y2="-50.8" width="0.1524" layer="91"/>
<pinref part="IC1" gate="G$1" pin="RF_P"/>
<wire x1="144.78" y1="-50.8" x2="109.22" y2="-50.8" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$5" class="0">
<segment>
<pinref part="U4" gate="G$1" pin="BAL3"/>
<pinref part="IC1" gate="G$1" pin="RF_N"/>
<wire x1="144.78" y1="-45.72" x2="109.22" y2="-45.72" width="0.1524" layer="91"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
<compatibility>
<note version="6.3" minversion="6.2.2" severity="warning">
Since Version 6.2.2 text objects can contain more than one line,
which will not be processed correctly with this version.
</note>
</compatibility>
</eagle>
