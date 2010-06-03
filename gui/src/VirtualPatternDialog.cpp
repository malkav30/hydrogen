/*
 * Hydrogen
 * Copyright(c) 2002-2008 by Alex >Comix< Cominu [comix@users.sourceforge.net]
 *
 * http://www.hydrogen-music.org
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY, without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *
 */

#include "VirtualPatternDialog.h"

#include <hydrogen/hydrogen.h>
#include <hydrogen/Song.h>
#include <hydrogen/sound_basic/pattern.h>
#include <hydrogen/sound_basic/pattern_list.h>

#include "Skin.h"

namespace
{

struct SimplePatternNode
{
    H2Core::Pattern *curPattern;
    int colour;
    std::set<H2Core::Pattern*> edges;
};//SimplePatternNode
    
void addEdges(std::set<H2Core::Pattern*>& patternSet)
{
    H2Core::Pattern::virtual_patterns_t curPatternSet = patternSet;
    
    for (H2Core::Pattern::virtual_patterns_cst_it_t setIter = curPatternSet.begin(); setIter != curPatternSet.end(); ++setIter) {
	 for (H2Core::Pattern::virtual_patterns_cst_it_t innerSetIter = (*setIter)->get_virtual_patterns()->begin(); innerSetIter != (*setIter)->get_virtual_patterns()->end(); ++innerSetIter) {
	     patternSet.insert(*innerSetIter);
	 }//for
    }//for
    
    if (patternSet.size() != curPatternSet.size()) {
	addEdges(patternSet);
    }//if
}//addEdges
    
}//anonymous namespace

const char* VirtualPatternDialog::__class_name = "VirtualPatternDialog";

VirtualPatternDialog::VirtualPatternDialog(QWidget* parent)
 : QDialog(parent)
 , Object( __class_name )
{
	setupUi( this );

	setFixedSize( width(), height() );
	setWindowTitle( trUtf8( "Select virtual pattern" ) );
}



VirtualPatternDialog::~VirtualPatternDialog()
{
}



void VirtualPatternDialog::on_cancelBtn_clicked()
{
	reject();
}



void VirtualPatternDialog::on_okBtn_clicked()
{
	accept();
}

void VirtualPatternDialog::computeVirtualPatternTransitiveClosure(H2Core::PatternList *pPatternList)
{
    //std::map<Pattern*, SimplePatternNode*> patternNodeGraph;
    
    int listsize = pPatternList->size();
    for (unsigned int index = 0; index < listsize; ++index) {
	H2Core::Pattern *curPattern = pPatternList->get(index);
	//SimplePatternNode *newNode = new SimplePatternNode();
	//newNode->curPattern = curPattern;
	//newNode->colour = 0;
	//newNode->edges = curPattern->virtual_pattern_set;
	
	//curPattern->set_virtual_pattern_transitive_closure_set( *curPattern->get_virtual_pattern_set() );
	curPattern->copy_virtual_patterns_to_transitive_closure( );
	
	addEdges( *curPattern->get_virtual_patterns_transitive_closure() );
	
	//patternNodeGraph[curPattern] = newNode;
    }//for
}//computeVirtualPatternTransitiveClosure


