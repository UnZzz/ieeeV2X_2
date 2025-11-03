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

import veins2.MyBaseApp;
//
// network description file for your Veins Application. Add parameters here
//
simple MyVeinsCarApp extends MyBaseApp
{
    parameters:
    @class(veins::MyVeinsCarApp);
    string appName = default("My first Veins App!");
    // double wsmInterval =default(50ms) @unit(ms);
    double avg_wsmInterval = default(1467us) @unit(us);
    volatile double wsmInterval=exponential(avg_wsmInterval) @unit(us);// full is 1467us
    
        @signal[MyVeinsCarApp_app_sigPktGenTime](type=double);//"veins::MyVeinsApp"
       // @statistic[pktGenTime](source=MyVeinsApp_app_sigPktGenTime; record= vector);
}
