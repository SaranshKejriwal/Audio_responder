#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>
#include<stdio.h>
using namespace cv;
using namespace std;

int main()
{
	Mat img,imgt,imgb;
	//img=imread("paul.jpg");
	//resize(img,img,Size(530,360));
	VideoCapture cap(0);
	//system("mplayer intro.mp3");
	namedWindow("Color");
	namedWindow("input");
	//namedWindow("mask");
	moveWindow("input",605,5);
	static int bl=0,gl=0,rl=72,bh=47,gh=46,rh=255;
	vector < vector < Point > >contours;
	int count=0;
	int flag=0;
	int X=0,Y=0;
	cout<<"__________Press l to know location_______\n";
	cout<<"__________Press b to break program_______\n";
	waitKey(30);
		
	for(;;)
	{
		count++;
		cap>>img;
		flip(img,img,1);
		line(img,Point(160,0),Point(160,480),Scalar(0,255,0),1);
		line(img,Point(320,0),Point(320,480),Scalar(0,255,0),1);
		line(img,Point(480,0),Point(480,480),Scalar(0,255,0),1);
		line(img,Point(0,240),Point(640,240),Scalar(0,255,0),1);
		putText(img,"1",Point(145,240),FONT_HERSHEY_DUPLEX,1,Scalar(0,250,255),3);
		putText(img,"2",Point(300,240),FONT_HERSHEY_DUPLEX,1,Scalar(0,250,255),3);
		putText(img,"3",Point(460,240),FONT_HERSHEY_DUPLEX,1,Scalar(0,250,255),3);
		putText(img,"4",Point(620,240),FONT_HERSHEY_DUPLEX,1,Scalar(0,250,255),3);
		putText(img,"5",Point(140,475),FONT_HERSHEY_DUPLEX,1,Scalar(0,250,255),3);
		putText(img,"6",Point(300,475),FONT_HERSHEY_DUPLEX,1,Scalar(0,250,255),3);
		putText(img,"7",Point(460,475),FONT_HERSHEY_DUPLEX,1,Scalar(0,250,255),3);
		putText(img,"8",Point(620,475),FONT_HERSHEY_DUPLEX,1,Scalar(0,250,255),3);
		createTrackbar("BL","Color",&bl,255);
		createTrackbar("GL","Color",&gl,255);
		createTrackbar("RL","Color",&rl,255);
				
		createTrackbar("BH","Color",&bh,255);
		createTrackbar("GH","Color",&gh,255);
		createTrackbar("RH","Color",&rh,255);
		
		inRange(img,Scalar(bl,gl,rl),Scalar(bh,gh,rh),imgt);
		//imshow("mask",imgt);//_______________________________________________________________________________
		findContours (imgt, contours, CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);//cause of unhandled exceptions
		cvtColor(imgt,imgt,CV_GRAY2BGR);


		for(int i=0;i<contours.size();i++)
					{
		 				if(contourArea(contours[i])>30)//to eliminate noise contours
			 				{
								drawContours (imgt, contours, -1, Scalar(0,200,200), 2);
								//drawContours (mask, contours, -1, color, 2);
							 }
						 
		 
					}
		int max=90,maxi=-10;
		vector<Rect> boundRect( contours.size() );
		for(int i=0;i<contours.size();i++)
					{
						 boundRect[i] = boundingRect( contours[i] );
					}
		for(int i=0;i<boundRect.size();i++)
					{
						if(boundRect[i].width*boundRect[i].height>max)
						 {
							max=boundRect[i].width*boundRect[i].height;
							maxi=i;
						 }
						//drawContours (imgt, contours2, -1, Scalar(0,255,0), 2);
						//drawContours (img, contours2, -1, Scalar(0,255,0), 2);
            
						//drawContours (draw, contours2[maxi], -1, Scalar(255,255,255), 4);
						//rectangle( draw, boundRect[maxi].tl(), boundRect[maxi].br(), Scalar(0,255,255),2,0);
			 
					}
		
		if(max>90 && maxi>=0)
					{
						
						//cout<<"largest rect index is "<<maxi<<"\n";
						//cout<<"largest rect area is "<<max<<"\n";
						rectangle(img,boundRect[maxi],Scalar(0,255,255),3,8);
						rectangle(imgt,boundRect[maxi],Scalar(0,255,255),3,8);
						
	
						putText(img,"Tracked",Point(boundRect[maxi].x,boundRect[maxi].y),FONT_HERSHEY_TRIPLEX,1.5,Scalar(0,250,255),1.5);
						//rectangle(imgt,boundRect[maxi],Scalar(0,255,255),3,8);
						putText(imgt,"Tracked",Point(boundRect[maxi].x,boundRect[maxi].y),FONT_HERSHEY_TRIPLEX,1.5,Scalar(0,250,255),1.5);

						Point trk_pnt=Point(boundRect[maxi].x+boundRect[maxi].width/2,boundRect[maxi].y+boundRect[maxi].height/2);

			    	    		//Point cursor=Point((boundRect[maxi].x)*1366/320,(boundRect[maxi].y)*768/480);
						circle(img,trk_pnt,2,Scalar(255,255,0),10);
						circle(imgt,trk_pnt,2,Scalar(255,255,0),10);				           	
						
						char text[10];
						X=trk_pnt.x;
						Y=trk_pnt.y;
						sprintf(text, "X=%d // Y= %d",X,Y);//to print a variable text on screen.
						putText(img,text,Point(10,30),FONT_HERSHEY_SIMPLEX,1,Scalar(250,250,250),2);		
						putText(imgt,text,Point(10,30),FONT_HERSHEY_SIMPLEX,1,Scalar(250,250,250),2);		
						

						

						
		

		
				}//end of if maxi>0 condition
			
		imshow("input",img);
		
		char c=waitKey(10);
		if(c=='l')//type l to know location
		{
			if(X<160 && Y<240 && X>1 && Y>1)
			{
				system("mplayer 1.mp3");			
			}
			if(X<320 && Y<240 && X>160 && Y>1)
			{
				system("mplayer 2.mp3");			
			}
			if(X<480 && Y<240 && X>320 && Y>1)
			{
				system("mplayer 3.mp3");			
			}
			if(X<640 && Y<240 && X>480 && Y>1)
			{
				system("mplayer 4.mp3");			
			}
			if(X<160 && X>1 && Y>240)
			{
				system("mplayer 5.mp3");			
			}
			if(X<320 && X>160 && Y>240)
			{
				system("mplayer 6.mp3");			
			}
			if(X<480 && X>320 && Y>240)
			{
				system("mplayer 7.mp3");			
			}
			if(X<640 && X>480 && Y>240)
			{
				system("mplayer 8.mp3");			
			}
			else
			{
				//system("mplayer 0.mp3");
			//use system("start C:\\path_to\\0.mp3"); for Windows
			}		
		}
		if(c=='b')
			break;
	}
	return 1;
			
	}
