/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "diffserv.h"


using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("FirstScriptExample");

int
main (int argc, char *argv[])
{
  CommandLine cmd;
  cmd.Parse (argc, argv);

  Time::SetResolution (Time::NS);
  LogComponentEnable ("DropTailQueue", LOG_LEVEL_INFO);
  LogComponentEnable ("DiffServ", LOG_LEVEL_INFO);
  LogComponentEnable ("UdpClient", LOG_LEVEL_ALL);
  LogComponentEnable ("UdpServer", LOG_LEVEL_ALL);

  NodeContainer nodes;
  nodes.Create (3);

    // n0-->n1
  PointToPointHelper pointToPoint;
  pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("4Mbps"));
  pointToPoint.SetChannelAttribute ("Delay", StringValue ("0ms"));


    //n1-->n2
    PointToPointHelper pointToPoint2;
                          //ns3::DiffServQueue
    pointToPoint2.SetQueue("ns3::SPQ<Packet>");
    pointToPoint2.SetDeviceAttribute ("DataRate", StringValue ("1Mbps"));
    pointToPoint2.SetChannelAttribute ("Delay", StringValue ("0ms"));
    Config::SetDefault ("ns3::SPQ<Packet>::ConfigPath", StringValue ("spq.json"));

    NetDeviceContainer devices;
    devices = pointToPoint.Install (nodes.Get(0), nodes.Get(1));


    NetDeviceContainer devices2;

    devices2 = pointToPoint2.Install (nodes.Get(1), nodes.Get(2));




  InternetStackHelper stack;
  stack.Install (nodes);

  Ipv4AddressHelper address;
  address.SetBase ("10.1.1.0", "255.255.255.0");

    Ipv4AddressHelper address2;
    address2.SetBase ("10.1.2.0", "255.255.255.0");

  Ipv4InterfaceContainer interfaces = address.Assign (devices);

    Ipv4InterfaceContainer interfaces2 = address2.Assign (devices2);
    Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

  UdpServerHelper udpServer (61);      //realtime transport protocol   priority  0  61 
  UdpServerHelper udpServer2 (53);  //DNS request , height priority  = 1  53


  ApplicationContainer serverApps = udpServer.Install (nodes.Get (2));
  serverApps.Start (Seconds (1.0));
  serverApps.Stop (Seconds (10.0));
  
    ApplicationContainer serverApps2 = udpServer2.Install (nodes.Get (2));
  serverApps2.Start (Seconds (1.0));
  serverApps2.Stop (Seconds (10.0));
  

  UdpClientHelper udpClient (interfaces2.GetAddress (1), 61);
  udpClient.SetAttribute ("MaxPackets", UintegerValue (10000));
  udpClient.SetAttribute ("Interval", TimeValue (Seconds (0.005)));
  udpClient.SetAttribute ("PacketSize", UintegerValue (1024));

  ApplicationContainer clientApps = udpClient.Install (nodes.Get (0));
  clientApps.Start (Seconds (1.0));
  clientApps.Stop (Seconds (9.0));
  
  
  // dns query client 
   UdpClientHelper udpClient2(interfaces2.GetAddress (1), 53); //
  udpClient2.SetAttribute ("MaxPackets", UintegerValue (3000));
  udpClient2.SetAttribute ("Interval", TimeValue (Seconds (0.005)));
  udpClient2.SetAttribute ("PacketSize", UintegerValue (1024));

  ApplicationContainer clientApps2 = udpClient2.Install (nodes.Get (0));
  clientApps2.Start (Seconds (3.0));
  clientApps2.Stop (Seconds (5.0));


  // this will record all the nodes in pointToPoint, n0 n1 n2
  pointToPoint.EnablePcapAll ("project2_pointToPoint");


  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}
