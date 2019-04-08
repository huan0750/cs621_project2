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
#include "./diffserv-queue.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("FirstScriptExample");

int
main (int argc, char *argv[])
{
  CommandLine cmd;
  cmd.Parse (argc, argv);

  Time::SetResolution (Time::NS);
    LogComponentEnable ("DropTailQueue", LOG_LEVEL_INFO);
  LogComponentEnable ("DiffServQueue", LOG_LEVEL_INFO);
  LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
  LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);

  NodeContainer nodes;
  nodes.Create (3);

    // n0-->n1
  PointToPointHelper pointToPoint;
  pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("4Mbps"));
  pointToPoint.SetChannelAttribute ("Delay", StringValue ("0ms"));


    //n1-->n2
    PointToPointHelper pointToPoint2;
                          //ns3::DiffServQueue
    pointToPoint2.SetQueue("ns3::DiffServQueue<Packet>");
    pointToPoint2.SetDeviceAttribute ("DataRate", StringValue ("1Mbps"));
    pointToPoint2.SetChannelAttribute ("Delay", StringValue ("0ms"));

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

  UdpServerHelper udpServer (9);


  ApplicationContainer serverApps = udpServer.Install (nodes.Get (2));
  serverApps.Start (Seconds (1.0));
  serverApps.Stop (Seconds (10.0));

  UdpClientHelper udpClient (interfaces2.GetAddress (1), 9);
  udpClient.SetAttribute ("MaxPackets", UintegerValue (1));
  udpClient.SetAttribute ("Interval", TimeValue (Seconds (1.0)));
  udpClient.SetAttribute ("PacketSize", UintegerValue (1024));

  ApplicationContainer clientApps = udpClient.Install (nodes.Get (0));
  clientApps.Start (Seconds (2.0));
  clientApps.Stop (Seconds (10.0));


  pointToPoint.EnablePcapAll ("project2_pointToPoint1");
  pointToPoint2.EnablePcapAll ("project2_pointToPoint2");

  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}
