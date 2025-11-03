//
// Copyright (C) 2016 David Eckhoff <david.eckhoff@fau.de>
//
// Documentation for these modules is at http://veins.car2x.org/
//
// SPDX-License-Identifier: GPL-2.0-or-later
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//

package veins2;
import org.car2x.veins.modules.application.ieee80211p.DemoBaseApplLayer;

//
// network description file for your Veins Application. Add parameters here
//
simple MyVeinsRSUApp extends MyBaseApp
{
    @class(veins::MyVeinsRSUApp);
    string appName = default("My first Veins RSU App!");
    
    // signal informing interested application about channel busy state
        @signal[MyVeinsRSUApp_app_sigPktDelay](type=double);
        @statistic[pktDelay](source=MyVeinsRSUApp_app_sigPktDelay; record=stats, vector?);
        
        @signal[MyVeinsRSUApp_app_sigReceivedPktGenTime](type=double);
        @statistic[receivedPktGenTime](source=MyVeinsRSUApp_app_sigReceivedPktGenTime; record=count, vector?);
        
        @signal[MyVeinsRSUApp_app_sigReceivedPktSendTime](type=double);
        @statistic[receivedPktSendTime](source=MyVeinsRSUApp_app_sigReceivedPktSendTime; record=count, vector?);
}
